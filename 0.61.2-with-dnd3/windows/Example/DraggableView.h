#pragma once

#include "winrt/Microsoft.ReactNative.h"

namespace winrt::Example::implementation {
	class DraggableView : public winrt::Windows::UI::Xaml::Controls::Border {

	public:
		DraggableView(Microsoft::ReactNative::IReactContext const& reactContext);

	private:
		Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };
	};
}
