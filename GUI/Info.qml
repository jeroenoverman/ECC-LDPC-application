import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.3
import QtQuick.Layouts 1.12

//property alias demo_page: demo_page
Page {
    id: info_page
    width: 600
    height: 400


    antialiasing: true
    property int margin: 10




//    header: Label {
//        text: qsTr("Info")
//        font.pixelSize: Qt.application.font.pixelSize * 2
//        padding: 10
//    }
    Flickable {
        id: listView
        width: parent.width
        height: parent.height
        contentWidth: parent.width
        contentHeight: pane.implicitHeight

        ScrollBar.vertical: ScrollBar {}

        Pane {
            id: pane
            width: parent.width
            bottomPadding: 35


            Column {
                id: main_layout
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.margins: margin
                spacing: 10

                Text {
                    id: info_text
                    textFormat: Text.StyledText
                    wrapMode: Text.WordWrap
                    width: parent.width
                    padding: 10
                    font.pointSize: 12
                    onLinkActivated: Qt.openUrlExternally(link)
                    text: qsTr('<h1>LDPC Demo</h1><p>Made by: Vito Kortbeek and Jeroen Overman<br>
<a href="https://github.com/jeroenoverman/ECC-LDPC-application">https://github.com/jeroenoverman/ECC-LDPC-application</a></p>
<h3><a id="NB_4"></a>NB</h3>
<p><em>When a specific configuration is set on the first tab switching to the other tabs will lead to the program beeing unresponsive for a period of time. The application is waiting for the LDPC simulation to be completed. The duration of this period is dependent on the size of the specified demo images. <strong>The worst-case wait time will be in the order of 10 seconds</strong> (depending on your PC specifications). Switching tabs without chaning the settings will not lead to re-executon of the simulation, but chaning the settings will.</em></p>
<h2>Topics:</h2>
<ul>
<li>About the Application</li>
<li>LDPC Decoding Strategies</li>
<li>Channel Properties</li>
<li>Interesting Configurations</li>
<li>Parity-check Matrix</li>
<li>Matrix Format (alist)</li>
<li>Compiling the Sources</li>
</ul>
<h2>About the Application</h2>
<p>This application is intended to demonstrate the <a href="https://en.wikipedia.org/wiki/Low-density_parity-check_code">Low-density parity-check (LDPC)</a> error correcting code.<br>
The main goals of the application are to:</p>
<ol>
<li>Visualise the effect of the Signal to Noise Ratio (SNR) and the ability to use LDPC to correct the data</li>
<li>Visualise the difference in effectiveness between bit flipping and belief propagation</li>
<li>The impact of the coding rate on the ability to correct data</li>
<li>Visualise different stages in the decoding process</li>
<li>Plot the SNR vs the BER for an un-encoded channel (not ECC), LDPC with Bit Flipping decoding and LDPC with Belief Propagation (Log Likelihood) decoding</li>
</ol>
<p>These topics are represented in the application on different tabs (not necessarily in the order depicted above). The initial tab holds all the configuration settings used for all the other tabs.</p>
<h2>LDPC Decoding Strategies</h2>
<p>We offer two correcting/decoding strategies. One hard-decision decoder which uses the bit flipping method and one soft-in/soft-out decoder which based on belief propagation using log likelehood calculations, also known as the sum-product algorithm (SPA).<br>
The main differentiator is that bit flipping uses the already decoded binary values as input and makes decisions on which bit(s) to flip based on the number which bit(s) is/are the worst. Belief propagation however uses the “analog” channel input data do determine a certainty for every bit. This leads to belief propagation being better at decoding, at the price of more computation time (when implemented fully in software).</p>
<h2>Channel Properties</h2>
<p>The application simulates the sending and receiving of data over an analog channel using <a href="https://en.wikipedia.org/wiki/Phase-shift_keying">Binary Phase Shift Keying (BPSK)</a> modulation. The desired SNR setting (in dB) is used to apply <a href="https://en.wikipedia.org/wiki/Additive_white_Gaussian_noise">Additive white Gaussian noise (AWGN)</a> to the modulated signal creating the “received” data stream. This data stream is used by the LDPC core to correct the received data and the <a href="https://en.wikipedia.org/wiki/Bit_error_rate">bit error rate (BER)</a> is computed using the input data and the received data.</p>
<h2>Interesting Configurations</h2>
<p>These are the tipping point SNR settings per coding rate to achieve a BER of 0.</p>
<ul>
<li>Coding rate = 1/2
<ul>
<li>Belief propagation: <code>0dB</code></li>
<li>Bit flipping SNR: <code>5dB</code></li>
</ul>
</li>
<li>Coding rate = 2/3
<ul>
<li>Belief propagation: <code>1.7dB</code></li>
<li>Bit flipping SNR: <code>5dB</code></li>
</ul>
</li>
<li>Coding rate = 3/4
<ul>
<li>Belief propagation: <code>2.5dB</code></li>
<li>Bit flipping SNR: <code>5dB</code></li>
</ul>
</li>
<li>Coding rate = 5/6
<ul>
<li>Belief propagation: <code>3.4dB</code></li>
<li>Bit flipping SNR: <code>6dB</code></li>
</ul>
</li>
</ul>
<h2>Parity-check Matrix</h2>
<p>The LDPC encoding and decoding is done using a specified Parity-check Matrix (H matrix). This matrix can be constructed in numerous ways. This application uses the matrices specified in the WiFi 802.11n standard (Table R.1 page 481).<br>
The standard specifies Matrix prototypes for 4 different coding rates (1/2, 2/3, 3/4, 5/6). This application only implements a codeword block size of 648 because this is sufficient to show the effect of the coding rates. Data exceeding the block size for the specific coding rate is split up into multiple blocks.<br>
The standard specifies a method for creating the full Parity-check matrices from the prototype matrices on page 290 of the 802.11n standard. A script was created to convert the matrix prototype into a complete Parity-check matrix and the same matrix converted to the <code>alist</code> format (for reduced storage requirements and increased performance).<br>
The script can be found at: <a href="https://github.com/jeroenoverman/ECC-LDPC-application/blob/master/scripts/standard2alist.py">https://github.com/jeroenoverman/ECC-LDPC-application/blob/master/scripts/standard2alist.py</a></p>
<h3><a id="Detailed_Paritycheck_Matrix_specifications_55"></a>Detailed Parity-check Matrix specifications</h3>
<p>For more details check the 802.11n standard or inspect the <code>.alist</code> files.</p>
<h4>Coding rate = 1/2:</h4>
<p>Alist file: <code>H_n648-z27-r1_2.alist</code><br>
Type: Irregular<br>
N: 648<br>
M: 324<br>
K: 324<br>
Largest nr. 1’s N: 12<br>
Largest nr. 1’s M: 8</p>
<h4>Coding rate = 2/3:</h4>
<p>Alist file: <code>H_n648-z27-r2_3.alist</code><br>
Type: Irregular<br>
N: 648<br>
M: 216<br>
K: 432<br>
Largest nr. entries N: 8<br>
Largest nr. entries M: 11</p>
<h4>Coding rate = 3/4:</h4>
<p>Alist file: <code>H_n648-z27-r3_4.alist</code><br>
Type: Irregular<br>
N: 648<br>
M: 162<br>
K: 486<br>
Largest nr. entries N: 6<br>
Largest nr. entries M: 15</p>
<h4>Coding rate = 5/6:</h4>
<p>Alist file: <code>H_n648-z27-r3_4.alist</code><br>
Type: Irregular<br>
N: 648<br>
M: 108<br>
K: 540<br>
Largest nr. entries N: 4<br>
Largest nr. entries M: 22</p>
<h2>Matrix Format (alist)</h2>
<p>The Parity-check Matrix is rather large, but as it is sparse it can be stored in a more efficient way. One of these more efficient ways is using the <a href="http://www.inference.org.uk/mackay/codes/alist.html">alist</a> format. This format saves only saves data at non-zero entries of the matrix. This reduces the required size, but also speeds up the decoding and encoding processes. As these all loop through the Parity-check Matrix looking for non-zero entries.</p>
<h2>Compiling the Sources</h2>
<p>The application can be separated into two components. The core LDPC code and the visualization code.<br>
The core LDPC code is written in C++11 and included within the visualization code which is written using the <a href="https://www.qt.io/">QT framework</a>.<br>
To compile the whole project simply open the <code>GUI/LDPC.pro</code> file in QT Creator. To run the application the <code>*.alist</code> files need to be copied to the build directory (the directory containing the executable).</p>')    }

            }
        }
    }

}



