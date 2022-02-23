SecretBase_Text_TreeCanBeClimbed::
   .string "如果有藤蔓垂下来，\n就可以爬到树上去了。$"

SecretBase_Text_TreeUseSecretPower::
   .string "如果有藤蔓垂下来，\n就可以爬到树上去了。\p要使用神秘力量吗？$"

SecretBase_Text_VineDroppedDown::
   .string "粗大的藤蔓垂了下来！$"

SecretBase_Text_ClumpOfGrass::
   .string "如果弄掉这丛草，\n就可以进去了。$"

SecretBase_Text_ClumpUseSecretPower::
   .string "如果弄掉这丛草，\n就可以进去了。\p要使用神秘力量吗？$"

SecretBase_Text_DiscoveredSmallEntrance::
   .string "发现了小小的入口！$"

	.include "data/text/secret_base_trainers.inc"

SecretBase_EventScript_CheckEntrance::
	special GetSecretBaseTypeInFrontOfPlayer
	special CheckPlayerHasSecretBase
	compare VAR_RESULT, TRUE
	goto_if_eq SecretBase_EventScript_AlreadyHasSecretBase
	checkpartymove MOVE_SECRET_POWER
	setfieldeffectargument 0, VAR_RESULT
	buffermovename 1, MOVE_SECRET_POWER
	compare VAR_0x8007, SECRET_BASE_RED_CAVE
	goto_if_eq SecretBase_EventScript_Cave
	compare VAR_0x8007, SECRET_BASE_BROWN_CAVE
	goto_if_eq SecretBase_EventScript_Cave
	compare VAR_0x8007, SECRET_BASE_BLUE_CAVE
	goto_if_eq SecretBase_EventScript_Cave
	compare VAR_0x8007, SECRET_BASE_YELLOW_CAVE
	goto_if_eq SecretBase_EventScript_Cave
	compare VAR_0x8007, SECRET_BASE_TREE
	goto_if_eq SecretBase_EventScript_Tree
	compare VAR_0x8007, SECRET_BASE_SHRUB
	goto_if_eq SecretBase_EventScript_Shrub
	end

SecretBase_EventScript_Cave::
	lockall
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq SecretBase_EventScript_CaveNoSecretPower
	bufferpartymonnick 0, VAR_RESULT
	msgbox SecretBase_Text_IndentUseSecretPower, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_CancelOnEntrance
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	dofieldeffect FLDEFF_USE_SECRET_POWER_CAVE
	waitstate
	goto SecretBase_EventScript_CaveEnter
	end

SecretBase_EventScript_CaveUseSecretPower::
	lockall
	dofieldeffect FLDEFF_USE_SECRET_POWER_CAVE
	waitstate
	goto SecretBase_EventScript_CaveEnter
	end

SecretBase_EventScript_CaveNoSecretPower::
	msgbox SecretBase_Text_SmallIndentInWall, MSGBOX_DEFAULT
	releaseall
	end

SecretBase_EventScript_CaveEnter::
	msgbox SecretBase_Text_DiscoveredSmallCavern, MSGBOX_DEFAULT
	goto SecretBase_EventScript_InitSecretBase
	end

SecretBase_EventScript_Tree::
	lockall
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq SecretBase_EventScript_TreeNoSecretPower
	bufferpartymonnick 0, VAR_RESULT
	msgbox SecretBase_Text_TreeUseSecretPower, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_CancelOnEntrance
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	dofieldeffect FLDEFF_USE_SECRET_POWER_TREE
	waitstate
	goto SecretBase_EventScript_TreeEnter
	end

SecretBase_EventScript_TreeUseSecretPower::
	lockall
	dofieldeffect FLDEFF_USE_SECRET_POWER_TREE
	waitstate
	goto SecretBase_EventScript_TreeEnter
	end

SecretBase_EventScript_TreeNoSecretPower::
	msgbox SecretBase_Text_TreeCanBeClimbed, MSGBOX_DEFAULT
	releaseall
	end

SecretBase_EventScript_TreeEnter::
	msgbox SecretBase_Text_VineDroppedDown, MSGBOX_DEFAULT
	goto SecretBase_EventScript_InitSecretBase
	end

SecretBase_EventScript_Shrub::
	lockall
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq SecretBase_EventScript_ShrubNoSecretPower
	bufferpartymonnick 0, VAR_RESULT
	msgbox SecretBase_Text_ClumpUseSecretPower, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_CancelOnEntrance
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	dofieldeffect FLDEFF_USE_SECRET_POWER_SHRUB
	waitstate
	goto SecretBase_EventScript_ShrubEnter
	end

SecretBase_EventScript_ShrubUseSecretPower::
	lockall
	dofieldeffect FLDEFF_USE_SECRET_POWER_SHRUB
	waitstate
	goto SecretBase_EventScript_ShrubEnter
	end

SecretBase_EventScript_ShrubNoSecretPower::
	msgbox SecretBase_Text_ClumpOfGrass, MSGBOX_DEFAULT
	releaseall
	end

SecretBase_EventScript_ShrubEnter::
	msgbox SecretBase_Text_DiscoveredSmallEntrance, MSGBOX_DEFAULT
	goto SecretBase_EventScript_InitSecretBase
	end

SecretBase_EventScript_InitSecretBase::
	closemessage
	playse SE_EXIT
	setvar VAR_INIT_SECRET_BASE, 0
	setflag FLAG_DECORATION_0
	special SetPlayerSecretBase
	special EnterSecretBase
	setvar VAR_0x8004, 0
	setvar VAR_0x8005, 0
	special InitSecretBaseDecorationSprites
	setvar VAR_SECRET_BASE_INITIALIZED, 1
	waitstate
	end

SecretBase_EventScript_FirstEntrance::
	applymovement OBJ_EVENT_ID_PLAYER, SecretBase_Movement_EnterBase
	waitmovement 0
	setvar VAR_INIT_SECRET_BASE, 1
	msgbox SecretBase_Text_WantToMakeYourSecretBaseHere, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SecretBase_EventScript_SetAsBase
	closemessage
	playse SE_EXIT
	special ClearAndLeaveSecretBase
	end

SecretBase_EventScript_SetAsBase::
	closemessage
	setflag FLAG_RECEIVED_SECRET_POWER
	special EnterNewlyCreatedSecretBase
	waitstate
	end

SecretBase_Movement_EnterBase:
	walk_up
	walk_up
	step_end

SecretBase_EventScript_Enter::
	lockall
	setvar VAR_INIT_SECRET_BASE, 1
	playse SE_EXIT
	special IsCurSecretBaseOwnedByAnotherPlayer
	compare VAR_RESULT, FALSE
	goto_if_eq SecretBase_EventScript_EnterPlayersBase
	clearflag FLAG_DECORATION_0
	special EnterSecretBase
	setvar VAR_SECRET_BASE_INITIALIZED, 0
	waitstate
	end

SecretBase_EventScript_EnterPlayersBase::
	setflag FLAG_DECORATION_0
	special EnterSecretBase
	setvar VAR_SECRET_BASE_INITIALIZED, 0
	waitstate
	end

SecretBase_EventScript_AlreadyHasSecretBase::
	checkpartymove MOVE_SECRET_POWER
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq SecretBase_EventScript_NoSecretPower
	setfieldeffectargument 0, VAR_RESULT
	setorcopyvar VAR_0x8004, VAR_RESULT
	lockall
	special GetSecretBaseNearbyMapName
	msgbox SecretBase_Text_WouldYouLikeToMoveBases, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_CancelOnEntrance
	msgbox SecretBase_Text_AllDecorationsWillBeReturned, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_CancelOnEntrance
	fadescreenswapbuffers FADE_TO_BLACK
	special MoveOutOfSecretBaseFromOutside
	closemessage
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox SecretBase_Text_MovingCompletedUseSecretPower, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_CancelOnEntrance
	bufferpartymonnick 0, VAR_0x8004
	buffermovename 1, MOVE_SECRET_POWER
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	closemessage
	compare VAR_0x8007, SECRET_BASE_RED_CAVE
	goto_if_eq SecretBase_EventScript_CaveUseSecretPower
	compare VAR_0x8007, SECRET_BASE_BROWN_CAVE
	goto_if_eq SecretBase_EventScript_CaveUseSecretPower
	compare VAR_0x8007, SECRET_BASE_BLUE_CAVE
	goto_if_eq SecretBase_EventScript_CaveUseSecretPower
	compare VAR_0x8007, SECRET_BASE_YELLOW_CAVE
	goto_if_eq SecretBase_EventScript_CaveUseSecretPower
	compare VAR_0x8007, SECRET_BASE_TREE
	goto_if_eq SecretBase_EventScript_TreeUseSecretPower
	compare VAR_0x8007, SECRET_BASE_SHRUB
	goto_if_eq SecretBase_EventScript_ShrubUseSecretPower
	releaseall
	end

SecretBase_EventScript_NoSecretPower::
	lockall
	compare VAR_0x8007, SECRET_BASE_RED_CAVE
	goto_if_eq SecretBase_EventScript_CaveNoSecretPower
	compare VAR_0x8007, SECRET_BASE_BROWN_CAVE
	goto_if_eq SecretBase_EventScript_CaveNoSecretPower
	compare VAR_0x8007, SECRET_BASE_BLUE_CAVE
	goto_if_eq SecretBase_EventScript_CaveNoSecretPower
	compare VAR_0x8007, SECRET_BASE_YELLOW_CAVE
	goto_if_eq SecretBase_EventScript_CaveNoSecretPower
	compare VAR_0x8007, SECRET_BASE_TREE
	goto_if_eq SecretBase_EventScript_TreeNoSecretPower
	compare VAR_0x8007, SECRET_BASE_SHRUB
	goto_if_eq SecretBase_EventScript_ShrubNoSecretPower
	end

SecretBase_EventScript_CancelOnEntrance::
	closemessage
	releaseall
	end

SecretBase_EventScript_SetDecorationFlags::
	setflag FLAG_DECORATION_1
	setflag FLAG_DECORATION_2
	setflag FLAG_DECORATION_3
	setflag FLAG_DECORATION_4
	setflag FLAG_DECORATION_5
	setflag FLAG_DECORATION_6
	setflag FLAG_DECORATION_7
	setflag FLAG_DECORATION_8
	setflag FLAG_DECORATION_9
	setflag FLAG_DECORATION_10
	setflag FLAG_DECORATION_11
	setflag FLAG_DECORATION_12
	setflag FLAG_DECORATION_13
	setflag FLAG_DECORATION_14
	return

SecretBase_EventScript_InitDecorations::
	setvar VAR_0x8004, 0
	setvar VAR_0x8005, 0
	special InitSecretBaseDecorationSprites
	setvar VAR_SECRET_BASE_INITIALIZED, 1
	end

SecretBase_EventScript_SetDecoration::
	setvar VAR_0x8005, 0
	goto SecretBase_EventScript_SetDecoration2
	end

SecretBase_EventScript_SetDecoration2::
	special SetDecoration
	end

SecretBase_EventScript_PutAwayDecoration::
	setvar VAR_0x8004, 0
	goto SecretBase_EventScript_PutAwayDecorationLoop
	end

SecretBase_EventScript_PutAwayDecorationLoop::
	special PutAwayDecorationIteration
	compare VAR_RESULT, 1
	goto_if_eq SecretBase_EventScript_PutAwayDecorationEnd
	addvar VAR_0x8004, 1
	compare VAR_0x8005, 0
	goto_if_eq SecretBase_EventScript_PutAwayDecorationLoop
	removeobject VAR_0x8006
	setflag VAR_0x8005  @ UB: VAR_0x8005 is set to a flag by PutAwayDecorationIteration, but ScrCmd_setflag doesn't use VarGet
	goto SecretBase_EventScript_PutAwayDecorationLoop
	end

SecretBase_EventScript_PutAwayDecorationEnd::
	end

SecretBase_EventScript_RecordMixTrainer::
	special GetSecretBaseOwnerAndState
	compare VAR_0x8004, 0
	goto_if_eq SecretBase_EventScript_Trainer0
	compare VAR_0x8004, 1
	goto_if_eq SecretBase_EventScript_Trainer1
	compare VAR_0x8004, 2
	goto_if_eq SecretBase_EventScript_Trainer2
	compare VAR_0x8004, 3
	goto_if_eq SecretBase_EventScript_Trainer3
	compare VAR_0x8004, 4
	goto_if_eq SecretBase_EventScript_Trainer4
	compare VAR_0x8004, 5
	goto_if_eq SecretBase_EventScript_Trainer5
	compare VAR_0x8004, 6
	goto_if_eq SecretBase_EventScript_Trainer6
	compare VAR_0x8004, 7
	goto_if_eq SecretBase_EventScript_Trainer7
	compare VAR_0x8004, 8
	goto_if_eq SecretBase_EventScript_Trainer8
	compare VAR_0x8004, 9
	goto_if_eq SecretBase_EventScript_Trainer9
	end

@ VAR_RESULT is initially set by GetSecretBaseOwnerAndState
SecretBase_EventScript_Trainer0::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SecretBase_EventScript_Trainer0PreChampion
	compare VAR_RESULT, 1
	goto_if_eq SecretBase_EventScript_Trainer0PostBattle
	msgbox SecretBase_Text_Trainer0Intro, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_Trainer0DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call Common_EventScript_SaveGame
	compare VAR_RESULT, 0
	goto_if_eq SecretBase_EventScript_Trainer0DeclineBattle
	msgbox SecretBase_Text_Trainer0AcceptBattle, MSGBOX_DEFAULT
	goto SecretBase_EventScript_BattleTrainer
	end

SecretBase_EventScript_Trainer0PreChampion::
	msgbox SecretBase_Text_Trainer0PreChampion, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer0DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox SecretBase_Text_Trainer0DeclineBattle, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer0PostBattle::
	msgbox SecretBase_Text_Trainer0PostBattle, MSGBOX_DEFAULT
	release
	end

@ VAR_RESULT is initially set by GetSecretBaseOwnerAndState
SecretBase_EventScript_Trainer1::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SecretBase_EventScript_Trainer1PreChampion
	compare VAR_RESULT, 1
	goto_if_eq SecretBase_EventScript_Trainer1PostBattle
	msgbox SecretBase_Text_Trainer1Intro, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_Trainer1DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call Common_EventScript_SaveGame
	compare VAR_RESULT, 0
	goto_if_eq SecretBase_EventScript_Trainer1DeclineBattle
	msgbox SecretBase_Text_Trainer1AcceptBattle, MSGBOX_DEFAULT
	goto SecretBase_EventScript_BattleTrainer
	end

SecretBase_EventScript_Trainer1PreChampion::
	msgbox SecretBase_Text_Trainer1PreChampion, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer1DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox SecretBase_Text_Trainer1DeclineBattle, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer1PostBattle::
	msgbox SecretBase_Text_Trainer1PostBattle, MSGBOX_DEFAULT
	release
	end

@ VAR_RESULT is initially set by GetSecretBaseOwnerAndState
SecretBase_EventScript_Trainer2::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SecretBase_EventScript_Trainer2PreChampion
	compare VAR_RESULT, 1
	goto_if_eq SecretBase_EventScript_Trainer2PostBattle
	msgbox SecretBase_Text_Trainer2Intro, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_Trainer2DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call Common_EventScript_SaveGame
	compare VAR_RESULT, 0
	goto_if_eq SecretBase_EventScript_Trainer2DeclineBattle
	msgbox SecretBase_Text_Trainer2AcceptBattle, MSGBOX_DEFAULT
	goto SecretBase_EventScript_BattleTrainer
	end

SecretBase_EventScript_Trainer2PreChampion::
	msgbox SecretBase_Text_Trainer2PreChampion, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer2DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox SecretBase_Text_Trainer2DeclineBattle, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer2PostBattle::
	msgbox SecretBase_Text_Trainer2PostBattle, MSGBOX_DEFAULT
	release
	end

@ VAR_RESULT is initially set by GetSecretBaseOwnerAndState
SecretBase_EventScript_Trainer3::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SecretBase_EventScript_Trainer3PreChampion
	compare VAR_RESULT, 1
	goto_if_eq SecretBase_EventScript_Trainer3PostBattle
	msgbox SecretBase_Text_Trainer3Intro, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_Trainer3DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call Common_EventScript_SaveGame
	compare VAR_RESULT, 0
	goto_if_eq SecretBase_EventScript_Trainer3DeclineBattle
	msgbox SecretBase_Text_Trainer3AcceptBattle, MSGBOX_DEFAULT
	goto SecretBase_EventScript_BattleTrainer
	end

SecretBase_EventScript_Trainer3PreChampion::
	msgbox SecretBase_Text_Trainer3PreChampion, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer3DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox SecretBase_Text_Trainer3DeclineBattle, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer3PostBattle::
	msgbox SecretBase_Text_Trainer3PostBattle, MSGBOX_DEFAULT
	release
	end

@ VAR_RESULT is initially set by GetSecretBaseOwnerAndState
SecretBase_EventScript_Trainer4::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SecretBase_EventScript_Trainer4PreChampion
	compare VAR_RESULT, 1
	goto_if_eq SecretBase_EventScript_Trainer4PostBattle
	msgbox SecretBase_Text_Trainer4Intro, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_Trainer4DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call Common_EventScript_SaveGame
	compare VAR_RESULT, 0
	goto_if_eq SecretBase_EventScript_Trainer4DeclineBattle
	msgbox SecretBase_Text_Trainer4AcceptBattle, MSGBOX_DEFAULT
	goto SecretBase_EventScript_BattleTrainer
	end

SecretBase_EventScript_Trainer4PreChampion::
	msgbox SecretBase_Text_Trainer4PreChampion, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer4DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox SecretBase_Text_Trainer4DeclineBattle, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer4PostBattle::
	msgbox SecretBase_Text_Trainer4PostBattle, MSGBOX_DEFAULT
	release
	end

@ VAR_RESULT is initially set by GetSecretBaseOwnerAndState
SecretBase_EventScript_Trainer5::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SecretBase_EventScript_Trainer5PreChampion
	compare VAR_RESULT, 1
	goto_if_eq SecretBase_EventScript_Trainer5PostBattle
	msgbox SecretBase_Text_Trainer5Intro, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_Trainer5DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call Common_EventScript_SaveGame
	compare VAR_RESULT, 0
	goto_if_eq SecretBase_EventScript_Trainer5DeclineBattle
	msgbox SecretBase_Text_Trainer5AcceptBattle, MSGBOX_DEFAULT
	goto SecretBase_EventScript_BattleTrainer
	end

SecretBase_EventScript_Trainer5PreChampion::
	msgbox SecretBase_Text_Trainer5PreChampion, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer5DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox SecretBase_Text_Trainer5DeclineBattle, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer5PostBattle::
	msgbox SecretBase_Text_Trainer5PostBattle, MSGBOX_DEFAULT
	release
	end

@ VAR_RESULT is initially set by GetSecretBaseOwnerAndState
SecretBase_EventScript_Trainer6::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SecretBase_EventScript_Trainer6PreChampion
	compare VAR_RESULT, 1
	goto_if_eq SecretBase_EventScript_Trainer6PostBattle
	msgbox SecretBase_Text_Trainer6Intro, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_Trainer6DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call Common_EventScript_SaveGame
	compare VAR_RESULT, 0
	goto_if_eq SecretBase_EventScript_Trainer6DeclineBattle
	msgbox SecretBase_Text_Trainer6AcceptBattle, MSGBOX_DEFAULT
	goto SecretBase_EventScript_BattleTrainer
	end

SecretBase_EventScript_Trainer6PreChampion::
	msgbox SecretBase_Text_Trainer6PreChampion, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer6DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox SecretBase_Text_Trainer6DeclineBattle, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer6PostBattle::
	msgbox SecretBase_Text_Trainer6PostBattle, MSGBOX_DEFAULT
	release
	end

@ VAR_RESULT is initially set by GetSecretBaseOwnerAndState
SecretBase_EventScript_Trainer7::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SecretBase_EventScript_Trainer7PreChampion
	compare VAR_RESULT, 1
	goto_if_eq SecretBase_EventScript_Trainer7PostBattle
	msgbox SecretBase_Text_Trainer7Intro, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_Trainer7DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call Common_EventScript_SaveGame
	compare VAR_RESULT, 0
	goto_if_eq SecretBase_EventScript_Trainer7DeclineBattle
	msgbox SecretBase_Text_Trainer7AcceptBattle, MSGBOX_DEFAULT
	goto SecretBase_EventScript_BattleTrainer
	end

SecretBase_EventScript_Trainer7PreChampion::
	msgbox SecretBase_Text_Trainer7PreChampion, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer7DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox SecretBase_Text_Trainer7DeclineBattle, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer7PostBattle::
	msgbox SecretBase_Text_Trainer7PostBattle, MSGBOX_DEFAULT
	release
	end

@ VAR_RESULT is initially set by GetSecretBaseOwnerAndState
SecretBase_EventScript_Trainer8::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SecretBase_EventScript_Trainer8PreChampion
	compare VAR_RESULT, 1
	goto_if_eq SecretBase_EventScript_Trainer8PostBattle
	msgbox SecretBase_Text_Trainer8Intro, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_Trainer8DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call Common_EventScript_SaveGame
	compare VAR_RESULT, 0
	goto_if_eq SecretBase_EventScript_Trainer8DeclineBattle
	msgbox SecretBase_Text_Trainer8AcceptBattle, MSGBOX_DEFAULT
	goto SecretBase_EventScript_BattleTrainer
	end

SecretBase_EventScript_Trainer8PreChampion::
	msgbox SecretBase_Text_Trainer8PreChampion, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer8DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox SecretBase_Text_Trainer8DeclineBattle, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer8PostBattle::
	msgbox SecretBase_Text_Trainer8PostBattle, MSGBOX_DEFAULT
	release
	end

@ VAR_RESULT is initially set by GetSecretBaseOwnerAndState
SecretBase_EventScript_Trainer9::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SecretBase_EventScript_Trainer9PreChampion
	compare VAR_RESULT, 1
	goto_if_eq SecretBase_EventScript_Trainer9PostBattle
	msgbox SecretBase_Text_Trainer9Intro, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SecretBase_EventScript_Trainer9DeclineBattle
	setvar VAR_RESULT, 1
	special SetBattledOwnerFromResult
	call Common_EventScript_SaveGame
	compare VAR_RESULT, 0
	goto_if_eq SecretBase_EventScript_Trainer9DeclineBattle
	msgbox SecretBase_Text_Trainer9AcceptBattle, MSGBOX_DEFAULT
	goto SecretBase_EventScript_BattleTrainer
	end

SecretBase_EventScript_Trainer9PreChampion::
	msgbox SecretBase_Text_Trainer9PreChampion, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer9DeclineBattle::
	special DeclinedSecretBaseBattle
	setvar VAR_RESULT, 0
	special SetBattledOwnerFromResult
	msgbox SecretBase_Text_Trainer9DeclineBattle, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_Trainer9PostBattle::
	msgbox SecretBase_Text_Trainer9PostBattle, MSGBOX_DEFAULT
	release
	end

SecretBase_EventScript_BattleTrainer::
	special PrepSecretBaseBattleFlags
	setvar VAR_0x8004, SPECIAL_BATTLE_SECRET_BASE
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	compare VAR_RESULT, B_OUTCOME_DREW
	call_if_eq SecretBase_EventScript_DrewSecretBaseBattle
	compare VAR_RESULT, B_OUTCOME_WON
	call_if_eq SecretBase_EventScript_WonSecretBaseBattle
	compare VAR_RESULT, B_OUTCOME_LOST
	call_if_eq SecretBase_EventScript_LostSecretBaseBattle
	special HealPlayerParty
	release
	end

SecretBase_EventScript_DrewSecretBaseBattle::
	special DrewSecretBaseBattle
	return

SecretBase_EventScript_WonSecretBaseBattle::
	special WonSecretBaseBattle
	return

SecretBase_EventScript_LostSecretBaseBattle::
	special LostSecretBaseBattle
	return

	.include "data/scripts/secret_power_tm.inc"

SecretBase_EventScript_DollInteract::
	special CheckInteractedWithFriendsDollDecor
	end

SecretBase_EventScript_CushionInteract::
	special CheckInteractedWithFriendsCushionDecor
	end

SecretBase_Text_AllDecorationsWillBeReturned::
   .string "秘密基地里的所有家具\n及装饰品都会回到电脑中，\p确定吗？$"

SecretBase_Text_WantToRegisterSecretBase::
   .string "想要设置\n{STR_VAR_1}的秘密基地吗？$"

SecretBase_Text_AlreadyRegisteredDelete::
   .string "数据已经设置，\n要删除吗？$"

SecretBase_Text_TooManyBasesDeleteSome::
   .string "最多能够设置10件物品，\p要设置其它物品必须\n先删除原有物品。$"

SecretBase_Text_RegistrationCompleted::
   .string "登录完成。$"

SecretBase_Text_DataUnregistered::
   .string "数据已删除。$"

SecretBase_Text_BootUpPC::
   .string "{PLAYER}登录了电脑。$"

SecretBase_Text_WhatWouldYouLikeToDo::
   .string "想要做什么？$"

SecretBase_Text_RegistryInfo::
   .string "一旦登录成功，除非训练师\n将其移动到其它地方，\l否则物品不会消失。\p如果将一件物品从登录列表中\n删除，那么另一件物品就\l可以取代它的位置。\p秘密基地最多可\n登录10件物品。$"

SecretBase_Text_BattleTowerShield::
   .string "一个记录在对战塔中连续\n胜利{STR_VAR_1}次的盾形{STR_VAR_2}。$"

SecretBase_Text_ToyTV::
   .string "一个仿真玩具电视，\n很容易与真品混淆。$"

SecretBase_Text_SeedotTV::
   .string "一个橡实果形状的玩具电视，\n好像就要滚动着离开一样…$"

SecretBase_Text_SkittyTV::
   .string "一个向尾喵形状的玩具电视，\n好像就要溜走一样…$"

SecretBase_Text_WouldYouLikeToMoveBases::
   .string "只能拥有一个秘密基地，\p要从{STR_VAR_1}的秘密\n基地搬过来吗？$"

SecretBase_Text_MovingCompletedUseSecretPower::
   .string "搬动完成。\p要使用神秘力量吗？$"
