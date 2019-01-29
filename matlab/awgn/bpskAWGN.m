 %https://nl.mathworks.com/matlabcentral/fileexchange/25922-ber-of-bpsk-in-awgn-channel
 %This program simulates BER of BPSK in AWGN channel%
 clear all; close all; clc;
 num_bit=100000;                          %Signal length 
 max_run=1;                              %Maximum number of iterations for a single SNR
 Eb=1;                                    %Bit energy
 SNRdB=0:1:9;                             %Signal to Noise Ratio (in dB)
 SNR=10.^(SNRdB/10);                      

 for count=1:length(SNR)                  %Beginning of loop for different SNR
     avgError=0;
     No=Eb/SNR(count);                    %Calculate noise power from SNR
     
     for run_time=1:max_run               %Beginning of loop for different runs
         %waitbar((((count-1)*max_run)+run_time-1)/(length(SNRdB)*max_run));
         Error=0;
         
         %data=randint(1,num_bit);         %Generate binary data source
         data=randi([0, 1], 1,num_bit);         %Generate binary data source

         s=2*data-1;                      %Baseband BPSK modulation
         
         %N=sqrt(No/2)*randn(1,num_bit);   %Generate AWGN
         N=sqrt(No/2)*randn(1,num_bit);   %Generate AWGN

         
         Y=s+N;                           %Received Signal
         
         for k=1:num_bit                  %Decision device taking hard decision and deciding error
             if ((Y(k)>0 && data(k)==0)||(Y(k)<0 && data(k)==1))
                 Error=Error+1;
             end
         end
        
         Error=Error/num_bit;             %Calculate error/bit
         avgError=avgError+Error;         %Calculate error/bit for different runs        
     end                                  %Termination of loop for different runs
     BER_sim(count)=avgError/max_run;     %Calculate BER for a particular SNR                                  
 end                                      %Termination of loop for different SNR 
 BER_th=(1/2)*erfc(sqrt(SNR));            %Calculate analytical BER
 
 semilogy(SNRdB,BER_th);              %Plot BER
 hold on
 semilogy(SNRdB,BER_sim, 'o');
 legend('Theoretical','Simulation');
 axis([min(SNRdB) max(SNRdB) 10^(-5) 1]);
 hold off
