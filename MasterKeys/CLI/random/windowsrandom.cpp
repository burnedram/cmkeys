#include "stdafx.h"
#include "windowsrandom.h"
#include <Windows.h>
#include <exception>

using namespace std;

#define CRYPT_FLAGS CRYPT_VERIFYCONTEXT | CRYPT_SILENT

static const char *GetErrorMessage(DWORD error) {
	LPSTR winText = nullptr;
	if (!FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
			(LPSTR)&winText,
			0,
			NULL)) {
		if (winText)
			LocalFree(winText);
		char *errorText = static_cast<char *>(malloc(256));
		snprintf(errorText, 256, "CryptAcquireContext failed with error code %d", error);
		return errorText;
	}
	
	size_t len = strlen(winText);
	char *errorText = static_cast<char *>(malloc(len + 1));
	memcpy(errorText, winText, len + 1);
	LocalFree(winText);
	return errorText;
}

WindowsRandom::WindowsRandom() :
	WindowsRandom(PROV_RSA_FULL) // All providers seems to be about as fast as any other
{
}

WindowsRandom::WindowsRandom(DWORD providerType) {
	if (!CryptAcquireContext(&_hProv, nullptr, nullptr, providerType, CRYPT_FLAGS)) {
		DWORD error = GetLastError();
		if (error == NTE_BAD_KEYSET) {
			if (!CryptAcquireContext(&_hProv, nullptr, nullptr, providerType, CRYPT_FLAGS | CRYPT_NEWKEYSET))
				throw exception(GetErrorMessage(GetLastError()));
		} else
			throw exception(GetErrorMessage(GetLastError()));
	}
}

WindowsRandom::~WindowsRandom() {
	if (_hProv)
		CryptReleaseContext(_hProv, 0);
}

template<typename T>
inline T WindowsRandom::Next() {
	T next;
	Fill(&next, sizeof(T));
	return next;
}

uint8_t WindowsRandom::Next8() {
	return Next<uint8_t>();
}

uint16_t WindowsRandom::Next16() {
	return Next<uint16_t>();
}
uint32_t WindowsRandom::Next32() {
	return Next<uint32_t>();
}

uint64_t WindowsRandom::Next64() {
	return Next<uint32_t>();
}

bool WindowsRandom::Fill(void *pBuffer, size_t bufferSize) {
	if (!_hProv)
		return false;
	return CryptGenRandom(_hProv, static_cast<DWORD>(bufferSize), static_cast<BYTE *>(pBuffer)) == TRUE; // BOOL to bool
}