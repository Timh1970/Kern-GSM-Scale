# GSMScaleGUI

GSMScaleGUI is a **QT** based application buit for communicating with a **Kern** balance such as the **Kern FCB12K1** 
to measure the weight of a given sheet to calculate its Grams per square meter (GSM).

It may be possible to make this work with other scales and devices however it is highly likely that you will need to
change VMIN and the control character which for the **Kern** scale is **'w'**.

# INSTALLATION
Open GSMScaleGUI.pro with QTCreator, you will be prompted to configure the project

The project was created with "**Desktop QT 6.3.0 GCC 64 bit**" so ideally select that kit and hit
"**Configure Project**"

The project should then just build and run without issue.

**NOTE:** The applciation only works on Linux based operating sytems.

# DOCUMENTATION
The documentation is generated by doxygen and is contained within the **./Documentation/Sourcedoc** path.
Just open index.html in that directory.

**NOTE** You will need to generate the doucmentation yourself, the (Doxyfile is incuded so if you create the direcotry **./Documentation/Sourcedoc** simply running **doxygen** in the main directory should generate the documentation for you.

The manual for the scale can be found in the main direcotry.

# LICENSING
The application is distributed under the LGPL licensing scheme as reqired by QT, you are free to modify
or reuse any of the source code that I have writen as you see fit.  

**THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.**
