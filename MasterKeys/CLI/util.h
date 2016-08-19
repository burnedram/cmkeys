#pragma once

SIZE_T GetProcessMemoryUsage();

std::vector<std::wstring> split(std::wstring const &input);

const std::wstring DeviceName(DEVICE_INDEX dev);
