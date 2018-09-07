strUrl = WScript.Arguments.Item(0) > wget.vbs
StrFile = WScript.Arguments.Item(1) >> wget.vbs
Const HTTPREQUEST_PROXYSETTING_DEFAULT = 0 >> wget.vbs
Const HTTPREQUEST_PROXYSETTING_PRECONFIG = 0 >> wget.vbs
Const HTTPREQUEST_PROXYSETTING_DIRECT = 1 >> wget.vbs
Const HTTPREQUEST_PROXYSETTING_PROXY = 2 >> wget.vbs
Dim http, varByteArray, strData, strBuffer, lngCounter, fs, ts >> wget.vbs
Err.Clear >> wget.vbs
Set http = Nothing >> wget.vbs
Set http = CreateObject("WinHttp.WinHttpRequest.5.1") >> wget.vbs
If http Is Nothing Then Set http = CreateObject("WinHttp.WinHttpRequest") >> wget.vbs 
If http Is Nothing Then Set http = CreateObject("MSXML2.ServerXMLHTTP") >> wget.vbs 
If http Is Nothing Then Set http = CreateObject("Microsoft.XMLHTTP") >> wget.vbs
http.Open "GET", strURL, False >> wget.vbs
http.Send >> wget.vbs
varByteArray = http.ResponseBody >> wget.vbs
Set http = Nothing >> wget.vbs
Set fs = CreateObject("Scripting.FileSystemObject") >> wget.vbs
Set ts = fs.CreateTextFile(StrFile, True) >> wget.vbs
strData = "" >> wget.vbs
strBuffer = "" >> wget.vbs
For lngCounter = 0 to UBound(varByteArray) >> wget.vbs
ts.Write Chr(255 And Ascb(Midb(varByteArray,lngCounter + 1, 1))) >> wget.vbs
Next >> wget.vbs
ts.Close >> wget.vbs
