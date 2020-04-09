#include "pch.h"
#include "ReactPackageProvider.h"

#include "NativeModules.h"

#include "DraggableViewManager.h"
#include "DroppableViewManager.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::Example::implementation
{

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept
{
    packageBuilder.AddViewManager(
        L"DraggableViewManager", []() { return winrt::make<DraggableViewManager>(); }
    );
    packageBuilder.AddViewManager(
        L"DroppableViewManager", []() { return winrt::make<DroppableViewManager>(); }
    );

    AddAttributedModules(packageBuilder);
}

} // namespace winrt::Example::implementation


