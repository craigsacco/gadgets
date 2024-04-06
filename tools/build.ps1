# Copyright (c) 2024 Craig Sacco
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# SPDX-License-Identifier: MIT

param(
     [Parameter()][ValidateSet("VS2022")][string] $Compiler = "VS2022"
)

$ErrorActionPreference = "Stop"

# Get number of CPUs on the host
$Processors = (Get-CimInstance Win32_ComputerSystem).NumberOfLogicalProcessors

if ($Compiler -eq "VS2022") {
    Push-Location -Path "build-vs17" | Out-Null
    Start-Process -FilePath cmake.exe -ArgumentList "--build . -- -maxcpucount:$($Processors)" -NoNewWindow -Wait
    #& cmake --build . -- -maxcpucount=($Processors)
    Pop-Location | Out-Null
}
