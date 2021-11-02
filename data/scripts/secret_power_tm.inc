Route111_Text_MakingRoomUseTMToMakeYourOwn::
   .string "那是什么？\n我在干什么？\p我想利用一个技能\n在这里打出我自己的地方。\p我知道！这个技能机器给你好了。\n用它也来造一个你自己的房间如何？$"

Route111_Text_ExplainSecretPower::
   .string "找一棵看上去可以垂下\n藤蔓的大树，\p在树前面使用神秘力量，\n一些藤蔓就会从树上滑落下来，\l这样你就能爬上树去了。\p你可以在上面找到很多\n放置你喜欢的东西的地方，\p它就成为了你自己的秘密空间…\n一个秘密基地！\p你也做一个吧。\p另外，你不一定要把\n秘密基地建在树上，\p试试对着石头墙壁上的\n小洞使用神秘力量吧。\p我也要去找些别的地方了，\n好了，再见！$"

Route111_Text_DontWantThis::
   .string "哦？你不想要？\n如果你改变主意了，就来告诉我，好吗？$"

Route111_Text_DontHaveAnyRoom::
   .string "哦？你没有地方拿它了。\p我会暂时保管它的，以后\n再来拿吧，好吗？$"

Route111_EventScript_SecretPowerMan::
	lock
	faceplayer
	msgbox Route111_Text_MakingRoomUseTMToMakeYourOwn, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route111_EventScript_GiveSecretPower
	msgbox Route111_Text_DontWantThis, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_GiveSecretPower::
	giveitem ITEM_TM43
	compare VAR_RESULT, FALSE
	goto_if_eq Route111_EventScript_NoRoomForSecretPower
	msgbox Route111_Text_ExplainSecretPower, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RECEIVED_SECRET_POWER
	clearflag FLAG_HIDE_SLATEPORT_CITY_TM_SALESMAN
	compare VAR_FACING, DIR_WEST
	call_if_eq Route111_EventScript_SecretPowerManExit
	compare VAR_FACING, DIR_EAST
	call_if_eq Route111_EventScript_SecretPowerManExit
	compare VAR_FACING, DIR_NORTH
	call_if_eq Route111_EventScript_SecretPowerManExitNorth
	removeobject VAR_LAST_TALKED
	release
	end

Route111_EventScript_SecretPowerManExit::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExit
	waitmovement 0
	return

Route111_EventScript_SecretPowerManExitNorth::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExitNorth
	waitmovement 0
	return

Route111_EventScript_NoRoomForSecretPower::
	msgbox Route111_Text_DontHaveAnyRoom, MSGBOX_DEFAULT
	release
	end

Route111_Movement_SecretPowerManExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

Route111_Movement_SecretPowerManExitNorth:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end
