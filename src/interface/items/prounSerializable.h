#pragma once
#include "prounDraggable.h"
#include "prounCurves.h"
#include "prounConnectable.h"

namespace proun {
    
    class Serializable : public Connectable
    {
    public:
        /* --------------------------------------------------------------
         # serialization
         #
         #
         #
         # -------------------------------------------------------------- */
        string serialize();
        void deSerialize(string serialized);
        string serializeConnections();
        virtual string customSerialize();
        virtual void customDeSerialize(string serialized);
    };
}
