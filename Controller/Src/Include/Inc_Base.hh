#pragma once

#include <Windows.h>
#include <winternl.h>
#include <functional>
#include <sstream>
#include <chrono>
#include <memory>
#include <array>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <ntstatus.h>
#pragma warning(pop)

//  cuz why not
#define AUTO		auto
#define EXTERN		extern
#define CONSTCA		const_cast
#define STATICCA	static_cast
#define REINTER		reinterpret_cast

using namespace std::chrono;
using namespace std::chrono_literals;