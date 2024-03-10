

#pragma once

#include <string>

namespace Gadgets
{
	namespace Core
	{
		class IObject
		{
		public:
			virtual std::string Type() const = 0;

		protected:
			IObject() = default;
			~IObject() = default;
		};
	}
}
