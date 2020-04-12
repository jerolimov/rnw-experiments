#pragma once

#include "winrt/Microsoft.ReactNative.h"

namespace winrt {
	using namespace Microsoft::ReactNative;

	using namespace Windows::Foundation;
	using namespace Windows::Foundation::Collections;

	using namespace Windows::UI;
	using namespace Windows::UI::Xaml;
	using namespace Windows::UI::Xaml::Controls;
	using namespace Windows::UI::Xaml::Input;
	using namespace Windows::UI::Xaml::Media;
} // namespace winrt

namespace winrt::Example::implementation {
	struct DraggableView {

	public:
		DraggableView(Microsoft::ReactNative::IReactContext const& reactContext);
		void Release();

		winrt::FrameworkElement GetView();

		//
		// Drag and Drop callbacks
		//
		void OnDragStarting(
			const winrt::UIElement& sender,
			const winrt::DragStartingEventArgs& args);
		void OnDropCompleted(
			const winrt::UIElement& sender,
			const winrt::DropCompletedEventArgs& args);
		fire_and_forget OnDataRequested(
			Windows::ApplicationModel::DataTransfer::DataProviderRequest const& request);

	private:
		Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };

		winrt::Windows::UI::Xaml::Controls::Border m_view{ nullptr };

		winrt::event_revoker<winrt::IUIElement> m_dragStartingRevoker;
	};
}
