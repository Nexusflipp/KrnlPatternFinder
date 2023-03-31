# Kernel Byte Pattern Finder
<p align="center"> 
    <a href="#" target="_blank"> <img src="https://img.shields.io/tokei/lines/github/nexusflipp/KrnlPatternFinder"/> </a>
    <a href="#" target="_blank"> <img src="https://img.shields.io/github/issues/nexusflipp/KrnlPatternFinder"/> </a>
    <a href="#" target="_blank"> <img src="https://img.shields.io/github/languages/top/nexusflipp/KrnlPatternFinder"/> </a> 
    <a href="#" target="_blank"> <img src="https://img.shields.io/github/last-commit/nexusflipp/KrnlPatternFinder"/> </a> 
    <a href="#" target="_blank"> <img src="https://img.shields.io/github/repo-size/nexusflipp/KrnlPatternFinder"/> </a> 
    <a href="#" target="_blank"> <img src="https://img.shields.io/github/languages/code-size/nexusflipp/KrnlPatternFinder"/> </a> 
</p>

This solution aims to make it easier to test kernel byte patterns. The solution consists of two sub-projects:
*   A kernel driver which queries all the necessary information through requests.
*   A usermode process which makes it easier to handle requests.

## Features Of The Driver
*   Is able to get the base address of system modules.
*   Is able to get basic information about the segments of system modules.
*   Is able to find byte patterns, and return the address of these (IDA style).
*   Is able to communicate with a usermode process via IOCTL requests.

## Features Of The Process
*   Is able to start and stop the kernel driver at will.
*   Is able to communicate with the driver via IOCTL requests.

### Expanding The Project
To add more drivers and patterns you simply have to update the DriverInfo array, located at:
`KrnlPatternFinder\Controller\Src\Patterns\Patterns.cc`

### Building The Solution
In order to build the solution you have to first install the Win [sdk](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/) and then the [wdk](https://learn.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk). Next you will need to head over to the Visual Studio Installer: `Modify -> Individual Components -> Search-> x64/x86 Spectre-mitigated libs (Latest)` and install it. After that you will have open the project settings of the driver and got to: `Driver Signing -> Test Certificate -> Create Test Certificate`. The last step is to compile the solution.

### Running the Solution
When you finished building the projects you have to be sure that your windows is running in test signing mode.
If it is not, paste the following command in a privileged powershell: `Bcdedit.exe -set TESTSIGNING ON` and restart your pc.
After that you can execute the Controller, and it will ask you to paste the full directory of the driver.

### Credits
*   [Pavel Yosifovich](https://scorpiosoftware.net/): For several awesome books that helped me a lot.
*   [Reactos](https://reactos.org/) and the [Vergilius Project](https://www.vergiliusproject.com/): For helping me keep my structures updated.
*   [DarthTon](https://github.com/DarthTon): For showing me how ioctl communication works.
*   [Microsoft](https://learn.microsoft.com/en-us/docs/): For their extensive Winapi documentation.
