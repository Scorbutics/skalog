#pragma once
#include <functional>

namespace ska {
    namespace process {
        using SignalAction = std::function<void(int)>;
        
        void SetupSignalHandler();

        void SignalHandlerAddAction(SignalAction action);
    }   
}
