#include "pch.h"

#include "DraggableView.h"

// Only for testing the view with a background SolidColorBrush
#include <winrt/Windows.UI.Xaml.Media.h>

#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.DragDrop.h>

#include <winrt/Windows.Storage.h>

namespace winrt {
    using namespace Microsoft::ReactNative;
    using namespace Windows::Foundation;
    using namespace Windows::UI;
    using namespace Windows::UI::Popups;
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Controls;
    using namespace Windows::UI::Xaml::Input;
    using namespace Windows::UI::Xaml::Media;
} // namespace winrt

namespace winrt::Example::implementation {

    DraggableView::DraggableView(winrt::IReactContext const& reactContext) : m_reactContext(reactContext) {

        auto const& color = winrt::Colors::AliceBlue();
        auto const& brush = winrt::Windows::UI::Xaml::Media::SolidColorBrush(color);
        Background(brush);

        CanDrag(true);

    }

}
