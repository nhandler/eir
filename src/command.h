#ifndef command_h
#define command_h

#include <map>
#include <list>
#include <tr1/functional>
#include "message.h"
#include <paludis/util/instantiation_policy.hh>

namespace eir
{
    class CommandRegistry :
        public paludis::InstantiationPolicy<CommandRegistry, paludis::instantiation_method::SingletonTag>
    {
        public:
            typedef std::tr1::function<void(const Message *)> handler;
            typedef struct _id { } *id;

            void dispatch(const Message *, bool = false);

            id add_handler(std::string, const handler &);
            id add_handler(std::string, unsigned int, const handler &);
            void remove_handler(id);

        private:
            struct IrcStringCmp {
                bool operator() (std::string, std::string);
            };
            typedef std::map<id, std::pair<unsigned int, handler> > HandlerList;
            typedef std::map<std::string, HandlerList, IrcStringCmp> HandlerMap;
            HandlerMap _handlers;
            void _dispatch(HandlerMap::iterator, const Message *, bool);
    };
}

#endif
