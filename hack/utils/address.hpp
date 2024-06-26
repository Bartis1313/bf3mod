#pragma once

#include <array>
#include <optional>

namespace memory
{
	enum class Dereference : size_t
	{
		ONCE = 1,
		TWICE,
		THREE
	};

	class AddressBase
	{
	protected:
		uintptr_t m_addr{ };

	public:
		AddressBase() = default;
		constexpr AddressBase(uintptr_t addr)
			: m_addr{ addr }
		{}

		// raw place in memory as offset
		constexpr auto getAddr() const { return m_addr; }
	};

	template<typename T>
	class Address : public AddressBase
	{
	public:
		constexpr Address() = default;
		// pass by offset
		constexpr Address(uintptr_t addr) :
			AddressBase{ addr }
		{}
		// pass by pointer
		constexpr Address(void* addr) :
			AddressBase{ reinterpret_cast<uintptr_t>(addr) }
		{}
		// pass by another addr
		template<typename U>
		constexpr Address(const Address<U>& other)
			: AddressBase{ other.getAddr() }
		{}

		// cast to anything
		template<typename U>
		constexpr auto cast() const { return Address<U>{ m_addr }; }
		constexpr auto add(uintptr_t extraOffset) const { return Address{ m_addr + extraOffset }; }
		constexpr auto sub(uintptr_t extraOffset) const { return Address{ m_addr - extraOffset }; }
		// dereference x times. Possible args are: 1, 2, 3.
		// There will for sure won't be a case for 4 level dereference. 3rd is very rare.
		constexpr auto deRef(Dereference times = Dereference::ONCE) const
		{
			auto addr = m_addr;
			for (size_t i = 0U; i < static_cast<size_t>(times); ++i)
				addr = *reinterpret_cast<uintptr_t*>(addr);

			return Address<T>{ addr };
		}
		// get as rel32
		constexpr auto rel(uintptr_t relOffset = 0x1, uintptr_t absOffset = 0x0) const
		{
			const auto jump = m_addr + relOffset;
			const auto target = *reinterpret_cast<decltype(jump)*>(jump);
			return Address<T>{ jump + absOffset + 0x4 + target };
		}
		// will work for classes types too
		constexpr T operator()() const
		{
			if constexpr (std::is_class_v<T>)
				return *reinterpret_cast<T*>(m_addr);
			else
				return (T)(m_addr);
		}

		constexpr T operator->() const
		{
			if constexpr (std::is_class_v<T>)
				return *reinterpret_cast<T*>(m_addr);
			else
				return (T)(m_addr);
		}
	};
}