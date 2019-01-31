# LDPC Demo
Made by: Vito Kortbeek and Jeroen Overman
https://github.com/jeroenoverman/ECC-LDPC-application

## Runing the application (Windows)
- Download the archive from the [release page](https://github.com/jeroenoverman/ECC-LDPC-application/releases)
- Extract the archive
- Run `LDPC.exe`

### NB
_When a specific configuration is set on the first tab switching to the other tabs will lead to the program beeing unresponsive for a period of time. The application is waiting for the LDPC simulation to be completed. The duration of this period is dependent on the size of the specified demo images. **The worst-case wait time will be in the order of 10 seconds** (depending on your PC specifications). Switching tabs without chaning the settings will not lead to re-executon of the simulation, but chaning the settings will._

## Topics:
* About the Application
* LDPC Decoding Strategies
* Channel Properties
* Interesting Configurations
* Parity-check Matrix
* Matrix Format (alist)
* Compiling the Sources

## About the Application
This application is intended to demonstrate the [Low-density parity-check (LDPC)] [1] error correcting code.
The main goals of the application are to:
1. Visualise the effect of the Signal to Noise Ratio (SNR) and the ability to use LDPC to correct the data
2. Visualise the difference in effectiveness between bit flipping and belief propagation
3. The impact of the coding rate on the ability to correct data
4. Visualise different stages in the decoding process
5. Plot the SNR vs the BER for an un-encoded channel (not ECC), LDPC with Bit Flipping decoding and LDPC with Belief Propagation (Log Likelihood) decoding

These topics are represented in the application on different tabs (not necessarily in the order depicted above). The initial tab holds all the configuration settings used for all the other tabs.

## LDPC Decoding Strategies
We offer two correcting/decoding strategies. One hard-decision decoder which uses the bit flipping method and one soft-in/soft-out decoder which based on belief propagation using log likelehood calculations, also known as the sum-product algorithm (SPA).
The main differentiator is that bit flipping uses the already decoded binary values as input and makes decisions on which bit(s) to flip based on the number which bit(s) is/are the worst. Belief propagation however uses the "analog" channel input data do determine a certainty for every bit. This leads to belief propagation being better at decoding, at the price of more computation time (when implemented fully in software).

## Channel Properties
The application simulates the sending and receiving of data over an analog channel using [Binary Phase Shift Keying (BPSK)][2] modulation. The desired SNR setting (in dB) is used to apply [Additive white Gaussian noise (AWGN)][3] to the modulated signal creating the "received" data stream. This data stream is used by the LDPC core to correct the received data and the [bit error rate (BER)] [4] is computed using the input data and the received data.

## Interesting Configurations
These are the tipping point SNR settings per coding rate to achieve a BER of 0.
- Coding rate = 1/2
    * Belief propagation: `0dB`
    * Bit flipping SNR: `5dB`
- Coding rate = 2/3
    * Belief propagation: `1.7dB`
    * Bit flipping SNR: `5dB`
- Coding rate = 3/4
    * Belief propagation: `2.5dB`
    * Bit flipping SNR: `5dB`
- Coding rate = 5/6
    * Belief propagation: `3.4dB`
    * Bit flipping SNR: `6dB`

## Parity-check Matrix
The LDPC encoding and decoding is done using a specified Parity-check Matrix (H matrix). This matrix can be constructed in numerous ways. This application uses the matrices specified in the WiFi 802.11n standard (Table R.1 page 481).
The standard specifies Matrix prototypes for 4 different coding rates (1/2, 2/3, 3/4, 5/6). This application only implements a codeword block size of 648 because this is sufficient to show the effect of the coding rates. Data exceeding the block size for the specific coding rate is split up into multiple blocks.
The standard specifies a method for creating the full Parity-check matrices from the prototype matrices on page 290 of the 802.11n standard. A script was created to convert the matrix prototype into a complete Parity-check matrix and the same matrix converted to the `alist` format (for reduced storage requirements and increased performance).
The script can be found at: https://github.com/jeroenoverman/ECC-LDPC-application/blob/master/scripts/standard2alist.py

### Detailed Parity-check Matrix specifications
For more details check the 802.11n standard or inspect the `.alist` files.
#### Coding rate = 1/2:
Alist file: `H_n648-z27-r1_2.alist`
Type: Irregular
N: 648
M: 324
K: 324
Largest nr. 1's N: 12
Largest nr. 1's M: 8

#### Coding rate = 2/3:
Alist file: `H_n648-z27-r2_3.alist`
Type: Irregular
N: 648
M: 216
K: 432
Largest nr. entries N: 8
Largest nr. entries M: 11

#### Coding rate = 3/4:
Alist file: `H_n648-z27-r3_4.alist`
Type: Irregular
N: 648
M: 162
K: 486
Largest nr. entries N: 6
Largest nr. entries M: 15

#### Coding rate = 5/6:
Alist file: `H_n648-z27-r3_4.alist`
Type: Irregular
N: 648
M: 108
K: 540
Largest nr. entries N: 4
Largest nr. entries M: 22

## Matrix Format (alist)
The Parity-check Matrix is rather large, but as it is sparse it can be stored in a more efficient way. One of these more efficient ways is using the [alist][5] format. This format saves only saves data at non-zero entries of the matrix. This reduces the required size, but also speeds up the decoding and encoding processes. As these all loop through the Parity-check Matrix looking for non-zero entries.

## Compiling the Sources
The application can be separated into two components. The core LDPC code and the visualization code.
The core LDPC code is written in C++11 and included within the visualization code which is written using the [QT framework][6].
To compile the whole project simply open the `GUI/LDPC.pro` file in QT Creator. To run the application the `*.alist` files need to be copied to the build directory (the directory containing the executable).

[1]: https://en.wikipedia.org/wiki/Low-density_parity-check_code
[2]: https://en.wikipedia.org/wiki/Phase-shift_keying
[3]: https://en.wikipedia.org/wiki/Additive_white_Gaussian_noise
[4]: https://en.wikipedia.org/wiki/Bit_error_rate
[5]: http://www.inference.org.uk/mackay/codes/alist.html
[6]: https://www.qt.io/
