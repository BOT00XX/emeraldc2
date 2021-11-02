MysteryEventScript_AlteringCave::
	setvaddress MysteryEventScript_AlteringCave
	addvar VAR_ALTERING_CAVE_WILD_SET, 1
	compare VAR_ALTERING_CAVE_WILD_SET, 10
	vgoto_if_ne MysteryEventScript_AlteringCave_
	setvar VAR_ALTERING_CAVE_WILD_SET, 0
MysteryEventScript_AlteringCave_:
	lock
	faceplayer
	vmessage sText_MysteryGiftAlteringCave
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftAlteringCave::
    .string "感谢使用\n神秘礼物系统。\p有传言说\n稀有宝可梦被发现了。\p发现者称其在\n103号公路的变化洞窟中。\p可能值得你去证实下这个传言。.string "
