BerryTreeScript::
	special ObjectEventInteractionGetBerryTreeData
	switch VAR_0x8004
	case BERRY_STAGE_SPARKLING, BerryTree_EventScript_Sparkling
	case BERRY_STAGE_NO_BERRY, BerryTree_EventScript_CheckSoil
	case BERRY_STAGE_PLANTED, BerryTree_EventScript_CheckBerryStage1
	case BERRY_STAGE_SPROUTED, BerryTree_EventScript_CheckBerryStage2
	case BERRY_STAGE_TALLER, BerryTree_EventScript_CheckBerryStage3
	case BERRY_STAGE_FLOWERING, BerryTree_EventScript_CheckBerryStage4
	case BERRY_STAGE_BERRIES, BerryTree_EventScript_CheckBerryFullyGrown
	end

BerryTree_EventScript_Sparkling::
	lockall
	message BerryTree_Text_ExclamationPoint
	waitmessage
	waitbuttonpress
	releaseall
	end

BerryTree_EventScript_CheckSoil::
	lock
	faceplayer
	specialvar VAR_RESULT, PlayerHasBerries
	compare VAR_RESULT, TRUE
	goto_if_eq BerryTree_EventScript_WantToPlant
	message BerryTree_Text_ItsSoftLoamySoil
	waitmessage
	waitbuttonpress
	release
	end

BerryTree_EventScript_WantToPlant::
	msgbox BerryTree_Text_WantToPlant, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BerryTree_EventScript_ChooseBerryToPlant
	compare VAR_RESULT, NO
	goto_if_eq BerryTree_EventScript_CancelPlanting
	end

BerryTree_EventScript_ChooseBerryToPlant::
	fadescreen FADE_TO_BLACK
	closemessage
	special Bag_ChooseBerry
	waitstate
	compare VAR_ITEM_ID, 0
	goto_if_eq BerryTree_EventScript_CancelPlanting
	removeitem VAR_ITEM_ID
	call BerryTree_EventScript_PlantBerry

BerryTree_EventScript_CancelPlanting::
	release
	end

BerryTree_EventScript_CheckBerryStage1::
	lockall
	special ObjectEventInteractionGetBerryCountString
	message BerryTree_Text_BerryGrowthStage1
	waitmessage
	waitbuttonpress
	goto BerryTree_EventScript_WantToWater

BerryTree_EventScript_CheckBerryStage2::
	lockall
	special ObjectEventInteractionGetBerryName
	message BerryTree_Text_BerryGrowthStage2
	waitmessage
	waitbuttonpress
	goto BerryTree_EventScript_WantToWater

BerryTree_EventScript_CheckBerryStage3::
	lockall
	special ObjectEventInteractionGetBerryName
	message BerryTree_Text_BerryGrowthStage3
	waitmessage
	waitbuttonpress
	goto BerryTree_EventScript_WantToWater

BerryTree_EventScript_CheckBerryStage4::
	call BerryTree_EventScript_GetCareAdverb
	lockall
	special ObjectEventInteractionGetBerryName
	message BerryTree_Text_BerryGrowthStage4
	waitmessage
	waitbuttonpress
	goto BerryTree_EventScript_WantToWater

@ VAR_0x8005 here is the number of times watered
@ Buffered by ObjectEventInteractionGetBerryTreeData
BerryTree_EventScript_GetCareAdverb::
	compare VAR_0x8005, 0
	goto_if_eq BerryTree_EventScript_SetAdverbPoor
	compare VAR_0x8005, 4
	goto_if_eq BerryTree_EventScript_SetAdverbGreat
	bufferstring 1, BerryTree_Text_CareAdverbGood
	return

BerryTree_EventScript_SetAdverbGreat::
	bufferstring 1, BerryTree_Text_CareAdverbGreat
	return

BerryTree_EventScript_SetAdverbPoor::
	bufferstring 1, BerryTree_Text_CareAdverbPoor
	return

@ VAR_0x8006 here is the number of berries
BerryTree_EventScript_CheckBerryFullyGrown::
	buffernumberstring 1, VAR_0x8006
	lock
	faceplayer
	special ObjectEventInteractionGetBerryCountString
	msgbox BerryTree_Text_WantToPick, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BerryTree_EventScript_PickBerry
	compare VAR_RESULT, NO
	goto_if_eq BerryTree_EventScript_CancelPickingBerry

BerryTree_EventScript_PickBerry::
	special ObjectEventInteractionPickBerryTree
	compare VAR_0x8004, 0
	goto_if_eq BerryTree_EventScript_BerryPocketFull
	special IncrementDailyPickedBerries
	special ObjectEventInteractionRemoveBerryTree
	message BerryTree_Text_PickedTheBerry
	playfanfare MUS_OBTAIN_BERRY
	waitmessage
	waitfanfare
	waitbuttonpress
	message BerryTree_Text_PutAwayBerry
	waitmessage
	waitbuttonpress
	release
	end

BerryTree_EventScript_BerryPocketFull::
	message BerryTree_Text_BerryPocketFull
	waitmessage
	waitbuttonpress
	release
	end

BerryTree_EventScript_CancelPickingBerry::
	message BerryTree_Text_BerryLeftUnpicked
	waitmessage
	waitbuttonpress
	release
	end

BerryTree_EventScript_ItemUsePlantBerry::
	lockall
	special ObjectEventInteractionGetBerryTreeData
	call BerryTree_EventScript_PlantBerry
	releaseall
	end

BerryTree_EventScript_WantToWater::
	checkitem ITEM_WAILMER_PAIL, 1
	compare VAR_RESULT, 0
	goto_if_eq BerryTree_EventScript_DontWater
	special ObjectEventInteractionGetBerryName
	msgbox BerryTree_Text_WantToWater, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BerryTree_EventScript_WaterBerry
	compare VAR_RESULT, NO
	goto_if_eq BerryTree_EventScript_DontWater

BerryTree_EventScript_DontWater::
	releaseall
	end

BerryTree_EventScript_ItemUseWailmerPail::
	special ObjectEventInteractionGetBerryTreeData
	lockall
BerryTree_EventScript_WaterBerry::
	special ObjectEventInteractionGetBerryName
	message BerryTree_Text_WateredTheBerry
	waitmessage
	special ObjectEventInteractionWaterBerryTree
	special DoWateringBerryTreeAnim
	waitstate
	message BerryTree_Text_PlantIsDelighted
	waitmessage
	waitbuttonpress
	releaseall
	end

BerryTree_EventScript_PlantBerry::
	special ObjectEventInteractionPlantBerryTree
	incrementgamestat GAME_STAT_PLANTED_BERRIES
	special IncrementDailyPlantedBerries
	special ObjectEventInteractionGetBerryCountString
	message BerryTree_Text_PlantedOneBerry
	waitmessage
	waitbuttonpress
	return

BerryTree_Text_ItsSoftLoamySoil::
   .string "是软软的土壤。$"

BerryTree_Text_WantToPlant::
   .string "是软软的土壤。\n要种树果吗？$"

BerryTree_Text_PlantedOneBerry::
   .string "{PLAYER}在软软的土壤里\n种下一个{STR_VAR_1}。$"

BerryTree_Text_BerryGrowthStage1::
   .string "这里种了一个{STR_VAR_1}。$"

BerryTree_Text_BerryGrowthStage2::
   .string "{STR_VAR_1}发芽了。$"

BerryTree_Text_BerryGrowthStage3::
   .string "{STR_VAR_1}越长越高了。$"

BerryTree_Text_BerryGrowthStage4::
   .string "{STR_VAR_1}的花开得\n{STR_VAR_2}。$"

BerryTree_Text_CareAdverbGreat::
   .string "非常美丽$"

BerryTree_Text_CareAdverbPoor::
   .string "真可爱$"

BerryTree_Text_CareAdverbGood::
   .string "很漂亮$"

BerryTree_Text_WantToPick::
   .string "发现了{STR_VAR_2}个{STR_VAR_1}！\p要摘下\n{STR_VAR_1}吗？$"

BerryTree_Text_PickedTheBerry::
   .string "{PLAYER}摘下了{STR_VAR_2}个{STR_VAR_1}。$"

BerryTree_Text_PutAwayBerry::
   .string "{PLAYER}把{STR_VAR_1}\n放进背包的树果口袋里。\p土壤又变成了\n松软的样子。$"

BerryTree_Text_BerryPocketFull::
   .string "背包的树果口袋满了，\p不能再拿{STR_VAR_1}了。$"

BerryTree_Text_BerryLeftUnpicked::
   .string "{PLAYER}把{STR_VAR_1}\n留在了树上。$"

BerryTree_Text_WantToWater::
   .string "想要用吼吼鲸洒水壶\n浇{STR_VAR_1}吗？$"

BerryTree_Text_WateredTheBerry::
   .string "{PLAYER}给{STR_VAR_1}浇了水。$"

BerryTree_Text_PlantIsDelighted::
   .string "植物好像很高兴的样子。$"

BerryTree_Text_ExclamationPoint::
   .string "!$"
