#include <luaT/luaT.h>
#include <Engine/CompositeUpdateHandler.h>
#include "../LuaUtil.h"
#include "../LuaUpdateHandler.h"

using namespace luaT;
using namespace xihad::ngn;
namespace xihad { namespace script
{
	static UpdateHandler* getUpdateHandler(lua_State* L, int idx) 
	{
		UpdateHandler* updater = 0;
		if (updater = checkarg<UpdateHandler*>(L, 2))
		{
			// It is a update handler
		}
		else if (lua_istable(L, 2))
		{
			// delegate it
			updater = new LuaUpdateHandler(LuaRef::fromIndex(L, 2));
		}
		else
		{
			luaL_typerror(L, 2, "appendUpdater requires table/UpdateHandler");
		}

		return updater;
	}

	static int appendUpdater(lua_State* L)
	{
		auto group = checkarg<CompositeUpdateHandler*>(L, 1);
		UpdateHandler* updater = getUpdateHandler(L, 2);
		push<bool>(L, group->appendChildHandler(updater));
		return 1;
	}

	static int prependUpdater(lua_State* L)
	{
		auto group = checkarg<CompositeUpdateHandler*>(L, 1);
		UpdateHandler* updater = getUpdateHandler(L, 2);
		push<bool>(L, group->prependChildHandler(updater));
		return 1;
	}

	luaT_static bool removeUpdaterImpl(CompositeUpdateHandler* group, 
		UpdateHandler* updater)
	{
		auto it = group->findChildHandler(updater);
		if (it == group->childHandlerEnd())
			return false;

		group->eraseChildHandler(it);
		return true;
	}}

	int luaopen_CompositeUpdateHandler(lua_State* L)
	{
		auto removeUpdater = luaT_cfunction(removeUpdaterImpl);

		luaT_defRegsBgn(cuhRegs)
			{ "appendUpdater", appendUpdater },
			{ "removeUpdater", removeUpdater},
			{ "prependUpdater", prependUpdater },

			{ "appendUpdateHandler", appendUpdater },
			{ "removeUpdateUpdater", removeUpdater},
			{ "prependUpdateHandler", prependUpdater },
		luaT_defRegsEnd
		MetatableFactory<CompositeUpdateHandler, UpdateHandler>::create(L, cuhRegs, 0);

		return 0;
	}
}}

