.set LOCALID_MC, 1
.set LOCALID_JUDGE, 2
.set LOCALID_CONTESTANT_1, 3
.set LOCALID_CONTESTANT_2, 4
.set LOCALID_CONTESTANT_3, 5
.set LOCALID_AUDIENCE_1, 6
.set LOCALID_AUDIENCE_3, 7
.set LOCALID_AUDIENCE_4, 8
.set LOCALID_AUDIENCE_5, 9
.set LOCALID_AUDIENCE_6, 10
.set LOCALID_AUDIENCE_7, 11
.set LOCALID_AUDIENCE_2, 12
.set LOCALID_POKEBALL, 13
.set LOCALID_CONTESTANT_4, 14
.set LOCALID_ARTIST, 15

@ Either ends or returns to EventScript_ContestReceptionist after submitting a contest entry
LilycoveCity_ContestLobby_EventScript_SpeakToContestReceptionist::
	lock
	faceplayer
	compare VAR_CONTEST_PRIZE_PICKUP, 0
	goto_if_ne LilycoveCity_ContestLobby_EventScript_PickUpPrize
	call_if_set FLAG_RECEIVED_POKEBLOCK_CASE, LilycoveCity_ContestLobby_EventScript_ReceptionWelcome
	call_if_unset FLAG_RECEIVED_POKEBLOCK_CASE, LilycoveCity_ContestLobby_EventScript_GivePokeblockCase
	goto LilycoveCity_ContestLobby_EventScript_AskEnterContest
	end

LilycoveCity_ContestLobby_EventScript_ReceptionWelcome::
	msgbox LilycoveCity_ContestLobby_Text_ContestReception, MSGBOX_DEFAULT
	return

LilycoveCity_ContestLobby_EventScript_GivePokeblockCase::
	msgbox LilycoveCity_ContestLobby_Text_ReceptionDontHavePokeblockCase, MSGBOX_DEFAULT
	giveitem ITEM_POKEBLOCK_CASE
	setflag FLAG_RECEIVED_POKEBLOCK_CASE
	msgbox LilycoveCity_ContestLobby_Text_NowThatWeveClearedThatUp, MSGBOX_DEFAULT
	return

LilycoveCity_ContestLobby_EventScript_PickUpPrize::
	msgbox LilycoveCity_ContestLobby_Text_PokemonWonWeHavePrize, MSGBOX_DEFAULT
	switch VAR_CONTEST_PRIZE_PICKUP
	case 4, LilycoveCity_ContestLobby_EventScript_GiveLuxuryBallAtCounter
	end

LilycoveCity_ContestLobby_EventScript_GiveLuxuryBallAtCounter::
	giveitem ITEM_LUXURY_BALL
	compare VAR_RESULT, FALSE
	goto_if_eq LilycoveCity_ContestLobby_EventScript_NoRoomForLuxuryBallAtCounter
	setvar VAR_CONTEST_PRIZE_PICKUP, 0
	closemessage
	release
	end

LilycoveCity_ContestLobby_EventScript_NoRoomForLuxuryBallAtCounter::
	call Common_EventScript_BagIsFull
	msgbox LilycoveCity_ContestLobby_Text_ComeBackForPrizeLater, MSGBOX_DEFAULT
	release
	end

LilycoveCity_ContestLobby_EventScript_AskEnterContest::
	message LilycoveCity_ContestLobby_Text_EnterContest1
	waitmessage
	multichoice 0, 0, MULTI_ENTERINFO, FALSE
	switch VAR_RESULT
	case 0, LilycoveCity_ContestLobby_EventScript_ChooseContestRank
	case 1, LilycoveCity_ContestLobby_EventScript_ContestInfo
	case 2, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	case MULTI_B_PRESSED, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	end

LilycoveCity_ContestLobby_EventScript_ContestInfo::
	message LilycoveCity_ContestLobby_Text_WhichTopic1
	waitmessage
	multichoice 0, 0, MULTI_CONTEST_INFO, FALSE
	switch VAR_RESULT
	case 0, LilycoveCity_ContestLobby_EventScript_ExplainContests
	case 1, LilycoveCity_ContestLobby_EventScript_ExplainContestTypes
	case 2, LilycoveCity_ContestLobby_EventScript_ExplainContestRanks
	case 3, LilycoveCity_ContestLobby_EventScript_AskEnterContest
	case MULTI_B_PRESSED, LilycoveCity_ContestLobby_EventScript_AskEnterContest
	end

LilycoveCity_ContestLobby_EventScript_ExplainContests::
	msgbox LilycoveCity_ContestLobby_Text_ExplainContests, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ContestInfo
	end

LilycoveCity_ContestLobby_EventScript_ExplainContestTypes::
	msgbox LilycoveCity_ContestLobby_Text_ExplainContestTypes, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ContestInfo
	end

LilycoveCity_ContestLobby_EventScript_ExplainContestRanks::
	msgbox LilycoveCity_ContestLobby_Text_ExplainContestRanks, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ContestInfo
	end

LilycoveCity_ContestLobby_EventScript_CancelEnterContest::
	msgbox LilycoveCity_ContestLobby_Text_ParticipateAnotherTime, MSGBOX_DEFAULT
	release
	end

LilycoveCity_ContestLobby_EventScript_ChooseContestMon::
	msgbox LilycoveCity_ContestLobby_Text_EnterWhichPokemon1, MSGBOX_DEFAULT
	choosecontestmon
	compare VAR_0x8004, 255
	goto_if_eq LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	special TryEnterContestMon
	compare VAR_RESULT, CANT_ENTER_CONTEST
	goto_if_eq LilycoveCity_ContestLobby_EventScript_CantEnterLowRank
	compare VAR_RESULT, CAN_ENTER_CONTEST_EQUAL_RANK
	goto_if_eq LilycoveCity_ContestLobby_EventScript_EnterMon
	compare VAR_RESULT, CAN_ENTER_CONTEST_HIGH_RANK
	goto_if_eq LilycoveCity_ContestLobby_EventScript_ConfirmEntryAlreadyWon
	compare VAR_RESULT, CANT_ENTER_CONTEST_EGG
	goto_if_eq LilycoveCity_ContestLobby_EventScript_CantEnterEgg
	compare VAR_RESULT, CANT_ENTER_CONTEST_FAINTED
	goto_if_eq LilycoveCity_ContestLobby_EventScript_CantEnterFainted
	end

LilycoveCity_ContestLobby_EventScript_ChooseContestRank::
	message LilycoveCity_ContestLobby_Text_EnterWhichRank
	waitmessage
	multichoice 0, 0, MULTI_CONTEST_RANK, FALSE
	switch VAR_RESULT
	case 0, LilycoveCity_ContestLobby_EventScript_EnterNormalRank
	case 1, LilycoveCity_ContestLobby_EventScript_EnterSuperRank
	case 2, LilycoveCity_ContestLobby_EventScript_EnterHyperRank
	case 3, LilycoveCity_ContestLobby_EventScript_EnterMasterRank
	case 4, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	case MULTI_B_PRESSED, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	end

LilycoveCity_ContestLobby_EventScript_EnterNormalRank::
	setvar VAR_CONTEST_RANK, CONTEST_RANK_NORMAL
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

LilycoveCity_ContestLobby_EventScript_EnterSuperRank::
	setvar VAR_CONTEST_RANK, CONTEST_RANK_SUPER
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

LilycoveCity_ContestLobby_EventScript_EnterHyperRank::
	setvar VAR_CONTEST_RANK, CONTEST_RANK_HYPER
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

LilycoveCity_ContestLobby_EventScript_EnterMasterRank::
	setvar VAR_CONTEST_RANK, CONTEST_RANK_MASTER
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestType
	end

@ The multichoice selection IDs are equal to the CATEGORY values
@ So rather than list the cases they just copy VAR_RESULT for a valid selection into VAR_CONTEST_CATEGORY
LilycoveCity_ContestLobby_EventScript_ChooseContestType::
	message LilycoveCity_ContestLobby_Text_EnterWhichContest1
	waitmessage
	multichoice 0, 0, MULTI_CONTEST_TYPE, FALSE
	switch VAR_RESULT
	case 5, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	case MULTI_B_PRESSED, LilycoveCity_ContestLobby_EventScript_CancelEnterContest
	copyvar VAR_CONTEST_CATEGORY, VAR_RESULT
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	end

LilycoveCity_ContestLobby_EventScript_CantEnterLowRank::
	msgbox LilycoveCity_ContestLobby_Text_MonNotQualifiedForRank, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	release
	end

@ Unused
LilycoveCity_ContestLobby_EventScript_ConfirmEntry::
	msgbox LilycoveCity_ContestLobby_Text_ConfirmContestMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	case YES, LilycoveCity_ContestLobby_EventScript_EnterMon
	end

LilycoveCity_ContestLobby_EventScript_ConfirmEntryAlreadyWon::
	msgbox LilycoveCity_ContestLobby_Text_AlreadyWonEnterAnyway, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	case YES, LilycoveCity_ContestLobby_EventScript_EnterMon
	end

LilycoveCity_ContestLobby_EventScript_CantEnterEgg::
	msgbox LilycoveCity_ContestLobby_Text_EggCannotTakePart, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	release
	end

LilycoveCity_ContestLobby_EventScript_CantEnterFainted::
	msgbox LilycoveCity_ContestLobby_Text_MonInNoConditionForContest, MSGBOX_DEFAULT
	goto LilycoveCity_ContestLobby_EventScript_ChooseContestMon
	release
	end

@ The return here is back to LilycoveCity_ContestLobby_EventScript_ContestReceptionist
LilycoveCity_ContestLobby_EventScript_EnterMon::
	msgbox LilycoveCity_ContestLobby_Text_YourMonIsEntryNum4, MSGBOX_DEFAULT
	closemessage
	releaseall
	setvar VAR_CONTEST_HALL_STATE, 1
	return

ContestHall_EventScript_DoContest::
	special LinkContestTryShowWirelessIndicator
	setvar VAR_0x8006, 0
	lockall
	applymovement LOCALID_CONTESTANT_4, ContestHall_Movement_Player4FaceUp
	waitmovement 0
	applymovement LOCALID_MC, ContestHall_Movement_MCWalkDown
	waitmovement 0
	releaseall
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_GetContestRankStringId
	call ContestHall_EventScript_GetContestCategory
	call ContestHall_EventScript_ContestGettingStarted
	call ContestHall_EventScript_ShowContestMons
	call ContestHall_EventScript_DoContestAppeals
	call ContestHall_EventScript_ContestResults
	call ContestHall_EventScript_GetWinnerObjEventId
	call ContestHall_EventScript_CongratulateWinner
	call ContestHall_EventScript_AudienceLookAround
	call ContestHall_EventScript_GiveWinnerPrize
	setvar VAR_CONTEST_HALL_STATE, 2
	return

ContestHall_EventScript_GetContestRankStringId::
	switch VAR_CONTEST_RANK
	case CONTEST_RANK_NORMAL, ContestHall_EventScript_GetNormalStringId
	case CONTEST_RANK_SUPER, ContestHall_EventScript_GetSuperStringId
	case CONTEST_RANK_HYPER, ContestHall_EventScript_GetHyperStringId
	case CONTEST_RANK_MASTER, ContestHall_EventScript_GetMasterStringId
	return

ContestHall_EventScript_GetNormalStringId::
	setvar VAR_0x8009, STDSTRING_NORMAL
	return

ContestHall_EventScript_GetSuperStringId::
	setvar VAR_0x8009, STDSTRING_SUPER
	return

ContestHall_EventScript_GetHyperStringId::
	setvar VAR_0x8009, STDSTRING_HYPER
	return

ContestHall_EventScript_GetMasterStringId::
	setvar VAR_0x8009, STDSTRING_MASTER
	return

@ This whole switch is equivalent to copyvar VAR_0x8008, VAR_CONTEST_CATEGORY
ContestHall_EventScript_GetContestCategory::
	switch VAR_CONTEST_CATEGORY
	case CONTEST_CATEGORY_COOL, ContestHall_EventScript_GetCategoryCool
	case CONTEST_CATEGORY_BEAUTY, ContestHall_EventScript_GetCategoryBeauty
	case CONTEST_CATEGORY_CUTE, ContestHall_EventScript_GetCategoryCute
	case CONTEST_CATEGORY_SMART, ContestHall_EventScript_GetCategorySmart
	case CONTEST_CATEGORY_TOUGH, ContestHall_EventScript_GetCategoryTough
	return

ContestHall_EventScript_GetCategoryCool::
	setvar VAR_0x8008, CONTEST_CATEGORY_COOL
	return

ContestHall_EventScript_GetCategoryBeauty::
	setvar VAR_0x8008, CONTEST_CATEGORY_BEAUTY
	return

ContestHall_EventScript_GetCategoryCute::
	setvar VAR_0x8008, CONTEST_CATEGORY_CUTE
	return

ContestHall_EventScript_GetCategorySmart::
	setvar VAR_0x8008, CONTEST_CATEGORY_SMART
	return

ContestHall_EventScript_GetCategoryTough::
	setvar VAR_0x8008, CONTEST_CATEGORY_TOUGH
	return

ContestHall_EventScript_ContestGettingStarted::
	buffercontesttypestring 1, VAR_0x8008
	bufferstdstring 2, VAR_0x8009
	call ContestHall_EventScript_GettingStarted
	lockall
	applymovement LOCALID_MC, ContestHall_Movement_MCBackUp
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_GettingStarted::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_GettingStartedLink
	lockall
	msgbox ContestHall_Text_GettingStartedParticipantsAsFollows, MSGBOX_DEFAULT
	releaseall
	return

ContestHall_EventScript_GettingStartedLink::
	specialvar VAR_RESULT, IsWirelessContest
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_GettingStartedWireless
	messageautoscroll ContestHall_Text_GettingStartedParticipantsAsFollowsLink
	waitmessage
	return

ContestHall_EventScript_GettingStartedWireless::
	messageautoscroll ContestHall_Text_GettingStartedWireless
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_ParticipantsAsFollows
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	return

ContestHall_EventScript_ShowContestMons::
	call ContestHall_EventScript_ContestantWalkToCenter
	call ContestHall_EventScript_ShowContestMonPic
	call ContestHall_EventScript_AudienceHeartEmotes
	call ContestHall_EventScript_AudienceReactToContestant
	call ContestHall_EventScript_ContestantReturn
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_TryWaitForLink
	addvar VAR_0x8006, 1
	compare VAR_0x8006, CONTESTANT_COUNT
	goto_if_ne ContestHall_EventScript_ShowContestMons
	call ContestHall_EventScript_AudienceVote
	setvar VAR_TEMP_1, 6
	return

ContestHall_EventScript_TryWaitForLink::
	specialvar VAR_RESULT, IsWirelessContest
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_WaitForLink
	return

ContestHall_EventScript_WaitForLink::
	special LinkContestWaitForConnection
	waitstate
	return

ContestHall_EventScript_ContestantWalkToCenter::
	compare VAR_0x8006, 0
	goto_if_eq ContestHall_EventScript_Player1WalkToCenter
	compare VAR_0x8006, 1
	goto_if_eq ContestHall_EventScript_Player2WalkToCenter
	compare VAR_0x8006, 2
	goto_if_eq ContestHall_EventScript_Player3WalkToCenter
	compare VAR_0x8006, 3
	goto_if_eq ContestHall_EventScript_Player4WalkToCenter
	return

ContestHall_EventScript_Player1WalkToCenter::
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_1, ContestHall_Movement_Player1WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_1
	return

ContestHall_EventScript_Player2WalkToCenter::
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_2, ContestHall_Movement_Player2WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_2
	return

ContestHall_EventScript_Player3WalkToCenter::
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_3, ContestHall_Movement_Player3WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_3
	return

ContestHall_EventScript_Player4WalkToCenter::
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement LOCALID_CONTESTANT_4, ContestHall_Movement_Player4WalkToCenter
	waitmovement 0
	releaseall
	setvar VAR_0x800B, LOCALID_CONTESTANT_4
	return

ContestHall_EventScript_ShowContestMonPic::
	special BufferContestTrainerAndMonNames
	addvar VAR_0x8006, 1
	buffernumberstring 1, VAR_0x8006
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_ContestantDelay32
	waitmovement 0
	releaseall
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_CheckIfContestWithRSPlayer
	addobject LOCALID_POKEBALL
	playse SE_LEDGE
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_ContestantDelay32
	waitmovement 0
	releaseall
	addvar VAR_0x8006, -1
	playse SE_BALL_OPEN
	special ShowContestEntryMonPic
	call ContestHall_EventScript_EntryXTrainersMon
	return

ContestHall_EventScript_EntryXTrainersMon::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_EntryXTrainersMonLink
	message ContestHall_Text_EntryXTrainersMon
	waitmessage
	return

ContestHall_EventScript_EntryXTrainersMonLink::
	messageautoscroll ContestHall_Text_EntryXTrainersMon
	waitmessage
	return

ContestHall_EventScript_AudienceVote::
	call ContestHall_EventScript_AudienceWillVote
	call ContestHall_EventScript_VotingUnderWay
	playse SE_M_ENCORE2
	waitmessage
	call ContestHall_EventScript_AudienceLookAround
	applymovement LOCALID_MC, ContestHall_Movement_MCFaceJudge2
	waitmovement 0
	applymovement LOCALID_JUDGE, ContestHall_Movement_JudgeFaceMC
	waitmovement 0
	delay 20
	applymovement LOCALID_MC, ContestHall_Movement_FaceContestants
	applymovement LOCALID_JUDGE, ContestHall_Movement_FaceContestants
	waitmovement 0
	return

ContestHall_EventScript_AudienceWillVote::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_AudienceWillVoteLink
	msgbox ContestHall_Text_SeenContestantsAudienceWillVote, MSGBOX_DEFAULT
	return

ContestHall_EventScript_AudienceWillVoteLink::
	specialvar VAR_RESULT, IsWirelessContest
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_AudienceWillVoteWireless
	messageautoscroll ContestHall_Text_SeenContestantsAudienceWillVote
	waitmessage
	return

ContestHall_EventScript_AudienceWillVoteWireless::
	messageautoscroll ContestHall_Text_WeveSeenContestants
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_AudienceWillVote
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_LetVotingBegin
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	return

ContestHall_EventScript_VotingUnderWay::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_VotingUnderWayLink
	message ContestHall_Text_VotingUnderWay
	return

ContestHall_EventScript_VotingUnderWayLink::
	messageautoscroll ContestHall_Text_VotingUnderWay
	call ContestHall_EventScript_TryWaitForLink
	return

ContestHall_EventScript_AudienceReactToContestant::
	call ContestHall_EventScript_TryWaitForLink
	applymovement LOCALID_MC, ContestHall_Movement_AudienceMemberLookLeft
	waitmovement 0
	playse SE_M_ENCORE2
	call ContestHall_EventScript_VObjectAudienceLookAround
	applymovement LOCALID_AUDIENCE_5, ContestHall_Movement_AudienceMemberLookRight
	applymovement LOCALID_AUDIENCE_2, ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_AUDIENCE_3, ContestHall_Movement_AudienceMemberLookRight
	waitmovement 0
	applymovement LOCALID_MC, ContestHall_Movement_AudienceMemberLookRight
	waitmovement 0
	applymovement LOCALID_AUDIENCE_6, ContestHall_Movement_AudienceMemberLookLeft
	applymovement LOCALID_AUDIENCE_7, ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_AUDIENCE_1, ContestHall_Movement_AudienceMemberLookUp
	applymovement LOCALID_AUDIENCE_4, ContestHall_Movement_AudienceMemberLookLeft
	waitmovement 0
	applymovement LOCALID_MC, ContestHall_Movement_MCLookAtJudge
	waitmovement 0
	applymovement LOCALID_MC, ContestHall_Movement_MCWalkInPlaceDown
	applymovement LOCALID_JUDGE, ContestHall_Movement_JudgeLookAtMC
	waitmovement 0
	releaseall
	call ContestHall_EventScript_TryWaitForLink
	return

@ For below VAR_TEMP_0 is the number of heart emotes to try to display in the audience
@ The number of hearts to try to display is based on the condition of the presented pokemon and the rank
@ For each heart to display a random audience member is chosen, and a new one chosen if they already displayed a heart
@ VAR_TEMP_1 through VAR_TEMP_8 represent each of the 8 audience members that are actual object events
@    and are set to 9 if they havent displayed a heart yet, and 1 if they have
ContestHall_EventScript_AudienceHeartEmotes::
	special GetContestMonCondition
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_NORMAL
	call_if_eq ContestHall_EventScript_GetNumberOfHeartsNormal
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_SUPER
	call_if_eq ContestHall_EventScript_GetNumberOfHeartsSuper
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_HYPER
	call_if_eq ContestHall_EventScript_GetNumberOfHeartsHyper
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_MASTER
	call_if_eq ContestHall_EventScript_GetNumberOfHeartsMaster
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	call_if_eq ContestHall_EventScript_GetNumberOfHeartsLink
	setvar VAR_TEMP_1, 9
	setvar VAR_TEMP_2, 9
	setvar VAR_TEMP_3, 9
	setvar VAR_TEMP_4, 9
	setvar VAR_TEMP_5, 9
	setvar VAR_TEMP_6, 9
	setvar VAR_TEMP_7, 9
	setvar VAR_TEMP_8, 9
	compare VAR_TEMP_0, 0
	call_if_gt ContestHall_EventScript_DisplayHearts
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_4, 0
	setvar VAR_TEMP_5, 0
	setvar VAR_TEMP_6, 0
	setvar VAR_TEMP_7, 0
	setvar VAR_TEMP_8, 0
	return

ContestHall_EventScript_DisplayHearts::
	setvar VAR_RESULT, 8
	special GenerateContestRand
	compare VAR_RESULT, 0
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember1
	compare VAR_RESULT, 1
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember2
	compare VAR_RESULT, 2
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember3
	compare VAR_RESULT, 3
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember4
	compare VAR_RESULT, 4
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember5
	compare VAR_RESULT, 5
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember6
	compare VAR_RESULT, 6
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember7
	compare VAR_RESULT, 7
	call_if_eq ContestHall_EventScript_TryDisplayHeartAudienceMember8
	compare VAR_TEMP_0, 0  @ Still more hearts to display
	goto_if_gt ContestHall_EventScript_DisplayHearts
	waitmovement 0
	return

ContestHall_EventScript_GetNumberOfHeartsNormal::
	compare VAR_0x8004, 80
	goto_if_gt ContestHall_EventScript_Set8Hearts
	compare VAR_0x8004, 70
	goto_if_gt ContestHall_EventScript_Set7Hearts
	compare VAR_0x8004, 60
	goto_if_gt ContestHall_EventScript_Set6Hearts
	compare VAR_0x8004, 50
	goto_if_gt ContestHall_EventScript_Set5Hearts
	compare VAR_0x8004, 40
	goto_if_gt ContestHall_EventScript_Set4Hearts
	compare VAR_0x8004, 30
	goto_if_gt ContestHall_EventScript_Set3Hearts
	compare VAR_0x8004, 20
	goto_if_gt ContestHall_EventScript_Set2Hearts
	compare VAR_0x8004, 10
	goto_if_gt ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

ContestHall_EventScript_GetNumberOfHeartsSuper::
	compare VAR_0x8004, 230
	goto_if_gt ContestHall_EventScript_Set8Hearts
	compare VAR_0x8004, 210
	goto_if_gt ContestHall_EventScript_Set7Hearts
	compare VAR_0x8004, 190
	goto_if_gt ContestHall_EventScript_Set6Hearts
	compare VAR_0x8004, 170
	goto_if_gt ContestHall_EventScript_Set5Hearts
	compare VAR_0x8004, 150
	goto_if_gt ContestHall_EventScript_Set4Hearts
	compare VAR_0x8004, 130
	goto_if_gt ContestHall_EventScript_Set3Hearts
	compare VAR_0x8004, 110
	goto_if_gt ContestHall_EventScript_Set2Hearts
	compare VAR_0x8004, 90
	goto_if_gt ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

ContestHall_EventScript_GetNumberOfHeartsHyper::
	compare VAR_0x8004, 380
	goto_if_gt ContestHall_EventScript_Set8Hearts
	compare VAR_0x8004, 350
	goto_if_gt ContestHall_EventScript_Set7Hearts
	compare VAR_0x8004, 320
	goto_if_gt ContestHall_EventScript_Set6Hearts
	compare VAR_0x8004, 290
	goto_if_gt ContestHall_EventScript_Set5Hearts
	compare VAR_0x8004, 260
	goto_if_gt ContestHall_EventScript_Set4Hearts
	compare VAR_0x8004, 230
	goto_if_gt ContestHall_EventScript_Set3Hearts
	compare VAR_0x8004, 200
	goto_if_gt ContestHall_EventScript_Set2Hearts
	compare VAR_0x8004, 170
	goto_if_gt ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

ContestHall_EventScript_GetNumberOfHeartsMaster::
	compare VAR_0x8004, 600
	goto_if_gt ContestHall_EventScript_Set8Hearts
	compare VAR_0x8004, 560
	goto_if_gt ContestHall_EventScript_Set7Hearts
	compare VAR_0x8004, 520
	goto_if_gt ContestHall_EventScript_Set6Hearts
	compare VAR_0x8004, 480
	goto_if_gt ContestHall_EventScript_Set5Hearts
	compare VAR_0x8004, 440
	goto_if_gt ContestHall_EventScript_Set4Hearts
	compare VAR_0x8004, 400
	goto_if_gt ContestHall_EventScript_Set3Hearts
	compare VAR_0x8004, 360
	goto_if_gt ContestHall_EventScript_Set2Hearts
	compare VAR_0x8004, 320
	goto_if_gt ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

ContestHall_EventScript_GetNumberOfHeartsLink::
	compare VAR_0x8004, 600
	goto_if_gt ContestHall_EventScript_Set8Hearts
	compare VAR_0x8004, 550
	goto_if_gt ContestHall_EventScript_Set7Hearts
	compare VAR_0x8004, 500
	goto_if_gt ContestHall_EventScript_Set6Hearts
	compare VAR_0x8004, 450
	goto_if_gt ContestHall_EventScript_Set5Hearts
	compare VAR_0x8004, 400
	goto_if_gt ContestHall_EventScript_Set4Hearts
	compare VAR_0x8004, 300
	goto_if_gt ContestHall_EventScript_Set3Hearts
	compare VAR_0x8004, 200
	goto_if_gt ContestHall_EventScript_Set2Hearts
	compare VAR_0x8004, 100
	goto_if_gt ContestHall_EventScript_Set1Heart
	setvar VAR_TEMP_0, 0
	return

ContestHall_EventScript_Set1Heart::
	setvar VAR_TEMP_0, 1
	return

ContestHall_EventScript_Set2Hearts::
	setvar VAR_TEMP_0, 2
	return

ContestHall_EventScript_Set3Hearts::
	setvar VAR_TEMP_0, 3
	return

ContestHall_EventScript_Set4Hearts::
	setvar VAR_TEMP_0, 4
	return

ContestHall_EventScript_Set5Hearts::
	setvar VAR_TEMP_0, 5
	return

ContestHall_EventScript_Set6Hearts::
	setvar VAR_TEMP_0, 6
	return

ContestHall_EventScript_Set7Hearts::
	setvar VAR_TEMP_0, 7
	return

ContestHall_EventScript_Set8Hearts::
	setvar VAR_TEMP_0, 8
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember1::
	compare VAR_TEMP_1, 1
	goto_if_eq ContestHall_EventScript_AudienceMember1AlreadyEmoted
	applymovement LOCALID_AUDIENCE_1, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_1, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember1AlreadyEmoted::
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember2::
	compare VAR_TEMP_2, 1
	goto_if_eq ContestHall_EventScript_AudienceMember2AlreadyEmoted
	applymovement LOCALID_AUDIENCE_2, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_2, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember2AlreadyEmoted::
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember3::
	compare VAR_TEMP_3, 1
	goto_if_eq ContestHall_EventScript_AudienceMember3AlreadyEmoted
	applymovement LOCALID_AUDIENCE_3, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_3, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember3AlreadyEmoted::
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember4::
	compare VAR_TEMP_4, 1
	goto_if_eq ContestHall_EventScript_Audience4MemberAlreadyEmoted
	applymovement LOCALID_AUDIENCE_4, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_4, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_Audience4MemberAlreadyEmoted::
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember5::
	compare VAR_TEMP_5, 1
	goto_if_eq ContestHall_EventScript_AudienceMember5AlreadyEmoted
	applymovement LOCALID_AUDIENCE_5, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_5, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember5AlreadyEmoted::
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember6::
	compare VAR_TEMP_6, 1
	goto_if_eq ContestHall_EventScript_AudienceMember6AlreadyEmoted
	applymovement LOCALID_AUDIENCE_6, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_6, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember6AlreadyEmoted::
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember7::
	compare VAR_TEMP_7, 1
	goto_if_eq ContestHall_EventScript_AudienceMember7AlreadyEmoted
	applymovement LOCALID_AUDIENCE_7, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_7, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember7AlreadyEmoted::
	return

ContestHall_EventScript_TryDisplayHeartAudienceMember8::
	compare VAR_TEMP_8, 1
	goto_if_eq ContestHall_EventScript_AudienceMember8AlreadyEmoted
	applymovement LOCALID_ARTIST, ContestHall_Movement_Heart
	playse SE_PIN
	delay 14
	setvar VAR_TEMP_8, 1
	addvar VAR_TEMP_0, -1
	return

ContestHall_EventScript_AudienceMember8AlreadyEmoted::
	return

ContestHall_EventScript_ContestantReturn::
	closemessage
	release
	removeobject LOCALID_POKEBALL
	special HideContestEntryMonPic
	call ContestHall_EventScript_TryWaitForLink
	switch VAR_0x8006
	case 0, ContestHall_EventScript_Player1WalkBack
	case 1, ContestHall_EventScript_Player2WalkBack
	case 2, ContestHall_EventScript_Player3WalkBack
	case 3, ContestHall_EventScript_Player4WalkBack
	return

ContestHall_EventScript_Player1WalkBack::
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_Player1WalkBack
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player2WalkBack::
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_Player2WalkBack
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player3WalkBack::
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_Player3WalkBack
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player4WalkBack::
	call ContestHall_EventScript_TryWaitForLink
	lockall
	applymovement VAR_0x800B, ContestHall_Movement_Player4WalkBack
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_DoContestAppeals::
	lockall
	applymovement LOCALID_MC, ContestHall_Movement_FaceContestants2
	waitmovement 0
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_LetsAppeal
	waitmessage
	applymovement LOCALID_MC, ContestHall_Movement_WalkStageLeft
	applymovement LOCALID_JUDGE, ContestHall_Movement_WalkStageRight
	waitmovement 0
	releaseall
	call ContestHall_EventScript_TryWaitForLink
	setvar VAR_TEMP_9, 1
	special LinkContestTryHideWirelessIndicator
	startcontest
	special LinkContestTryShowWirelessIndicator
	setvar VAR_TEMP_9, 0
	lockall
	applymovement LOCALID_MC, ContestHall_Movement_WalkStageRight
	applymovement LOCALID_JUDGE, ContestHall_Movement_WalkStageLeft
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_LetsAppeal::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_LetsAppealLink
	msgbox ContestHall_Text_VotingCompleteLetsAppeal, MSGBOX_DEFAULT
	return

ContestHall_EventScript_LetsAppealLink::
	specialvar VAR_RESULT, IsWirelessContest
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_LetsAppealWireless
	messageautoscroll ContestHall_Text_VotingCompleteLetsAppeal
	waitmessage
	return

ContestHall_EventScript_LetsAppealWireless::
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_VotingComplete
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_SecondStageOfJudging
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_LetsAppeal
	waitmessage
	call ContestHall_EventScript_TryWaitForLink
	return

ContestHall_EventScript_ContestResults::
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_ThatsItForJudging
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_ThankYouForAppeals
	call ContestHall_EventScript_TryWaitForLink
	applymovement LOCALID_MC, ContestHall_Movement_MCFaceJudge
	waitmovement 0
	call ContestHall_EventScript_JudgeLooksReady
	call ContestHall_EventScript_TryWaitForLink
	call ContestHall_EventScript_WeWillDeclareWinner
	call ContestHall_EventScript_TryWaitForLink
	applymovement LOCALID_MC, ContestHall_Movement_FaceContestants
	waitmovement 0
	closemessage
	releaseall
	special LinkContestTryHideWirelessIndicator
	setvar VAR_TEMP_9, 1
	showcontestresults
	setvar VAR_TEMP_9, 0
	playbgm MUS_CONTEST_WINNER, FALSE
	return

ContestHall_EventScript_ThatsItForJudging::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_ThatsItForJudgingLink
	msgbox ContestHall_Text_ThatsItForJudging, MSGBOX_DEFAULT
	return

ContestHall_EventScript_ThatsItForJudgingLink::
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_ThatsItForJudging
	waitmessage
	delay 30
	return

ContestHall_EventScript_ThankYouForAppeals::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_ThankYouForAppealsLink
	msgbox ContestHall_Text_ThankYouForAppeals, MSGBOX_DEFAULT
	return

ContestHall_EventScript_ThankYouForAppealsLink::
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_ThankYouForAppeals
	waitmessage
	delay 30
	return

ContestHall_EventScript_JudgeLooksReady::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_JudgeLooksReadyLink
	msgbox ContestHall_Text_JudgeLooksReady, MSGBOX_DEFAULT
	return

ContestHall_EventScript_JudgeLooksReadyLink::
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_JudgeLooksReady
	waitmessage
	delay 30
	return

ContestHall_EventScript_WeWillDeclareWinner::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_WeWillDeclareWinnerLink
	msgbox ContestHall_Text_WeWillNowDeclareWinner, MSGBOX_DEFAULT
	return

ContestHall_EventScript_WeWillDeclareWinnerLink::
	call ContestHall_EventScript_TryWaitForLink
	messageautoscroll ContestHall_Text_WeWillNowDeclareWinner
	waitmessage
	delay 30
	return

ContestHall_EventScript_GetWinnerObjEventId::
	special GetContestWinnerId
	switch VAR_0x8005
	case 0, ContestHall_EventScript_GetPlayer1ObjEventId
	case 1, ContestHall_EventScript_GetPlayer2ObjEventId
	case 2, ContestHall_EventScript_GetPlayer3ObjEventId
	case 3, ContestHall_EventScript_GetPlayer4ObjEventId
	return

ContestHall_EventScript_GetPlayer1ObjEventId::
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_1
	return

ContestHall_EventScript_GetPlayer2ObjEventId::
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_2
	return

ContestHall_EventScript_GetPlayer3ObjEventId::
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_3
	return

ContestHall_EventScript_GetPlayer4ObjEventId::
	setvar VAR_TEMP_3, LOCALID_CONTESTANT_4
	return

ContestHall_EventScript_CongratulateWinner::
	special BufferContestWinnerTrainerName
	special BufferContestWinnerMonName
	addvar VAR_0x8005, 1
	buffernumberstring 1, VAR_0x8005
	addvar VAR_0x8005, -1
	call ContestHall_EventScript_CongratsWinner
	applymovement VAR_TEMP_3, ContestHall_Movement_WinningPlayerWalkUp
	waitmovement 0
	playse SE_M_ENCORE2
	setvar VAR_TEMP_1, 0
	return

ContestHall_EventScript_CongratsWinner::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_CongratsWinnerLink
	msgbox ContestHall_Text_CongratsTrainerXandMon, MSGBOX_DEFAULT
	return

ContestHall_EventScript_CongratsWinnerLink::
	messageautoscroll ContestHall_Text_CongratsTrainerXandMon
	waitmessage
	return

ContestHall_EventScript_AudienceLookAround::
	addvar VAR_TEMP_1, 1
	lockall
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_NORMAL
	call_if_gt ContestHall_EventScript_VObjectAudienceLookAround
	applymovement LOCALID_AUDIENCE_5, ContestHall_Movement_AudienceMemberLookRight
	applymovement LOCALID_AUDIENCE_2, ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_AUDIENCE_3, ContestHall_Movement_AudienceMemberLookRight
	delay 30
	applymovement LOCALID_AUDIENCE_6, ContestHall_Movement_AudienceMemberLookLeft
	applymovement LOCALID_AUDIENCE_7, ContestHall_Movement_AudienceMemberLookDown
	applymovement LOCALID_AUDIENCE_1, ContestHall_Movement_AudienceMemberLookUp
	applymovement LOCALID_AUDIENCE_4, ContestHall_Movement_AudienceMemberLookLeft
	compare VAR_TEMP_1, 4
	goto_if_ne ContestHall_EventScript_AudienceLookAround
	delay 30
	return

ContestHall_EventScript_VObjectAudienceLookAround::
	turnvobject 0, DIR_SOUTH
	turnvobject 2, DIR_SOUTH
	turnvobject 4, DIR_EAST
	turnvobject 6, DIR_SOUTH
	turnvobject 8, DIR_SOUTH
	turnvobject 10, DIR_SOUTH
	turnvobject 12, DIR_SOUTH
	turnvobject 14, DIR_SOUTH
	turnvobject 16, DIR_SOUTH
	turnvobject 18, DIR_SOUTH
	turnvobject 20, DIR_EAST
	turnvobject 22, DIR_EAST
	turnvobject 25, DIR_EAST
	turnvobject 27, DIR_WEST
	turnvobject 28, DIR_EAST
	delay 10
	turnvobject 0, DIR_EAST
	turnvobject 2, DIR_EAST
	turnvobject 4, DIR_EAST
	turnvobject 6, DIR_EAST
	turnvobject 8, DIR_EAST
	turnvobject 10, DIR_WEST
	turnvobject 12, DIR_WEST
	turnvobject 14, DIR_WEST
	turnvobject 16, DIR_WEST
	turnvobject 18, DIR_WEST
	turnvobject 20, DIR_SOUTH
	turnvobject 22, DIR_SOUTH
	turnvobject 25, DIR_NORTH
	turnvobject 27, DIR_NORTH
	turnvobject 28, DIR_NORTH
	delay 10
	turnvobject 1, DIR_NORTH
	turnvobject 3, DIR_NORTH
	turnvobject 5, DIR_NORTH
	turnvobject 7, DIR_NORTH
	turnvobject 9, DIR_EAST
	turnvobject 11, DIR_NORTH
	turnvobject 15, DIR_NORTH
	turnvobject 13, DIR_NORTH
	turnvobject 17, DIR_NORTH
	turnvobject 19, DIR_NORTH
	turnvobject 21, DIR_WEST
	turnvobject 23, DIR_WEST
	turnvobject 24, DIR_WEST
	turnvobject 26, DIR_EAST
	turnvobject 29, DIR_WEST
	turnvobject 30, DIR_WEST
	delay 10
	turnvobject 1, DIR_EAST
	turnvobject 3, DIR_EAST
	turnvobject 5, DIR_EAST
	turnvobject 7, DIR_EAST
	turnvobject 9, DIR_EAST
	turnvobject 11, DIR_WEST
	turnvobject 15, DIR_WEST
	turnvobject 13, DIR_WEST
	turnvobject 17, DIR_WEST
	turnvobject 19, DIR_WEST
	turnvobject 21, DIR_SOUTH
	turnvobject 23, DIR_SOUTH
	turnvobject 24, DIR_SOUTH
	turnvobject 26, DIR_NORTH
	turnvobject 29, DIR_NORTH
	turnvobject 30, DIR_NORTH
	delay 10
	return

ContestHall_EventScript_GiveWinnerPrize::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_LINK
	goto_if_eq ContestHall_EventScript_EndLinkContest
	call ContestHall_EventScript_CheckShouldSkipPrize
	goto_if_set FLAG_TEMP_2, ContestHall_EventScript_SkipPrize
	lockall
	msgbox ContestHall_Text_AcceptYourPrize, MSGBOX_DEFAULT
	releaseall
	call ContestHall_EventScript_WinnerApproachForPrize
	call ContestHall_EventScript_GivePrizeIfWinner
	playse SE_M_ENCORE2
	setvar VAR_TEMP_1, 0
	call ContestHall_EventScript_AudienceLookAround
	delay 30
	special ShouldReadyContestArtist
	compare VAR_0x8004, TRUE
	goto_if_eq ContestHall_EventScript_SetReadyForContestArtist
	return

ContestHall_EventScript_SkipPrize::
	lockall
	msgbox ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	delay 90
	special ShouldReadyContestArtist
	compare VAR_0x8004, TRUE
	goto_if_eq ContestHall_EventScript_SetReadyForContestArtist
	return

ContestHall_EventScript_CheckShouldSkipPrize::
	specialvar VAR_RESULT, HasMonWonThisContestBefore
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_CheckPlayerWon
	return

ContestHall_EventScript_CheckPlayerWon::
	special GetContestWinnerId
	compare VAR_0x8005, 3
	goto_if_eq ContestHall_EventScript_CheckRankIsMaster
	return

ContestHall_EventScript_CheckRankIsMaster::
	compare VAR_CONTEST_RANK, CONTEST_RANK_MASTER
	goto_if_eq ContestHall_EventScript_DontSkipPrize
	setflag FLAG_TEMP_2
	return

ContestHall_EventScript_DontSkipPrize::
	return

@ This flag is never read
ContestHall_EventScript_SetSketchFlag::
	setflag FLAG_CONTEST_SKETCH_CREATED
	return

ContestHall_EventScript_SetReadyForContestArtist::
	setvar VAR_LILYCOVE_CONTEST_LOBBY_STATE, 1
	return

ContestHall_EventScript_EndLinkContest::
	delay 60
	special GetContestPlayerId
	special GetContestWinnerId
	special ShouldReadyContestArtist
	compare VAR_0x8004, TRUE
	goto_if_eq ContestHall_EventScript_SetReadyForLinkContestArtist
	closemessage
	return

ContestHall_EventScript_SetReadyForLinkContestArtist::
	setvar VAR_LILYCOVE_CONTEST_LOBBY_STATE, 2
	return

@ Unused
ContestHall_EventScript_Ret::
	return

ContestHall_EventScript_WinnerApproachForPrize::
	switch VAR_0x8005
	case 0, ContestHall_EventScript_Player1ApproachForPrize
	case 1, ContestHall_EventScript_Player2ApproachForPrize
	case 2, ContestHall_EventScript_Player3ApproachForPrize
	case 3, ContestHall_EventScript_Player4ApproachForPrize
	return

ContestHall_EventScript_Player1ApproachForPrize::
	lockall
	applymovement VAR_TEMP_3, ContestHall_Movement_Player1ApproachForPrize
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player2ApproachForPrize::
	lockall
	applymovement VAR_TEMP_3, ContestHall_Movement_Player2ApproachForPrize
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player3ApproachForPrize::
	lockall
	applymovement VAR_TEMP_3, ContestHall_Movement_Player3ApproachForPrize
	waitmovement 0
	releaseall
	return

ContestHall_EventScript_Player4ApproachForPrize::
	lockall
	applymovement VAR_TEMP_3, ContestHall_Movement_Player4ApproachForPrize
	waitmovement 0
	releaseall
	return

@ In NPC Contests, the player is always entry 4 (id number 3)
ContestHall_EventScript_GivePrizeIfWinner::
	special GetContestWinnerId
	compare VAR_0x8005, 3
	goto_if_eq ContestHall_EventScript_GiveContestPrizes
	lockall
	msgbox ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	return

ContestHall_EventScript_GiveContestPrizes::
	compare VAR_CONTEST_TYPE, CONTEST_TYPE_NPC_SUPER
	call_if_eq ContestHall_EventScript_SetSketchFlag
	specialvar VAR_RESULT, HasMonWonThisContestBefore
	compare VAR_RESULT, FALSE
	goto_if_eq ContestHall_EventScript_ReceiveContestRibbon
	compare VAR_CONTEST_RANK, CONTEST_RANK_MASTER
	goto_if_eq ContestHall_EventScript_GiveLuxuryBall
	lockall
	msgbox ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	return

ContestHall_EventScript_NoRoomForLuxuryBall::
	lockall
	call Common_EventScript_BagIsFull
	msgbox ContestHall_Text_PickUpPrizeAtCounterLater, MSGBOX_DEFAULT
	releaseall
	setvar VAR_CONTEST_PRIZE_PICKUP, 4
	return

ContestHall_EventScript_GiveLuxuryBall::
	giveitem ITEM_LUXURY_BALL
	compare VAR_RESULT, FALSE
	goto_if_eq ContestHall_EventScript_NoRoomForLuxuryBall
	lockall
	msgbox ContestHall_Text_CongratsPleaseCompeteAgain, MSGBOX_DEFAULT
	releaseall
	return

ContestHall_EventScript_ReceiveContestRibbon::
	special GiveMonContestRibbon
	incrementgamestat GAME_STAT_RECEIVED_RIBBONS
	setflag FLAG_SYS_RIBBON_GET
	lockall
	msgbox ContestHall_Text_ConferRibbonAsPrize, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	msgbox ContestHall_Text_ReceivedRibbon, MSGBOX_DEFAULT
	waitfanfare
	special BufferContestWinnerMonName
	msgbox ContestHall_Text_PutRibbonOnMon, MSGBOX_DEFAULT
	releaseall
	return

ContestHall_Movement_MCWalkDown:
	walk_down
	step_end

ContestHall_Movement_MCBackUp:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

ContestHall_Movement_MCFaceJudge:
	walk_in_place_fastest_right
	step_end

ContestHall_Movement_Heart:
	emote_heart
	step_end

ContestHall_Movement_FaceContestants:
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_WalkStageLeft:
	walk_left
	walk_left
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_WalkStageRight:
	walk_right
	walk_right
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_WinningPlayerWalkUp:
	walk_up
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_ContestantDelay32:
	delay_16
	delay_16
	step_end

ContestHall_Movement_MCFaceJudge2:
	walk_in_place_fastest_right
	step_end

ContestHall_Movement_JudgeFaceMC:
	walk_in_place_fastest_left
	step_end

ContestHall_Movement_FaceContestants2:
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_Player3ApproachForPrize:
	walk_left
	walk_left
	walk_up
	step_end

ContestHall_Movement_Player4ApproachForPrize:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

ContestHall_Movement_AudienceMemberLookLeft:
	face_left
	delay_16
	face_original_direction
	step_end

ContestHall_Movement_AudienceMemberLookUp:
	face_up
	delay_16
	face_original_direction
	step_end

ContestHall_Movement_AudienceMemberLookRight:
	face_right
	delay_16
	face_original_direction
	step_end

ContestHall_Movement_AudienceMemberLookDown:
	face_down
	delay_16
	face_original_direction
	step_end

ContestHall_Movement_Player4FaceUp:
	face_up
	step_end

ContestHall_Movement_MCLookAtJudge:
	face_up
	delay_16
	walk_in_place_fastest_right
	step_end

ContestHall_Movement_JudgeLookAtMC:
	walk_in_place_fastest_left
	delay_16
	delay_16
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_MCWalkInPlaceDown:
	delay_16
	delay_16
	walk_in_place_fastest_down
	step_end

ContestHall_Movement_Player1WalkToCenter:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player1WalkBack:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player2WalkToCenter:
	walk_up
	walk_right
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player2WalkBack:
	walk_fast_left
	walk_fast_down
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player3WalkToCenter:
	walk_up
	walk_left
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player3WalkBack:
	walk_fast_right
	walk_fast_down
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player4WalkToCenter:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player4WalkBack:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_in_place_fastest_up
	step_end

ContestHall_Movement_Player1ApproachForPrize:
	walk_right
	walk_right
	walk_up
	step_end

ContestHall_Movement_Player2ApproachForPrize:
	walk_up
	step_end

@ IsContestWithRSPlayer has no side effect, so this is nop
ContestHall_EventScript_CheckIfContestWithRSPlayer::
	specialvar VAR_RESULT, IsContestWithRSPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq ContestHall_EventScript_RetRSPlayer
	return

ContestHall_EventScript_RetRSPlayer::
	return

LilycoveCity_ContestLobby_EventScript_DelayIfContestWithRSPlayer::
	specialvar VAR_RESULT, IsContestWithRSPlayer
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_ContestLobby_EventScript_DelayForRSPlayer
	return

LilycoveCity_ContestLobby_EventScript_DelayForRSPlayer::
	delay 9
	return

LilycoveCity_ContestLobby_Text_ReceptionDontHavePokeblockCase::
   .string "你好！\p这里是宝可梦华丽大赛的\n服务前台。\p哎呀？好像你还没拿到\n能量方块盒吧。\p这样的话，我们就提供\n一个给你吧！$"

LilycoveCity_ContestLobby_Text_NowThatWeveClearedThatUp::
   .string "OK，\n现在我们弄清楚了…\p你好！\p这里是宝可梦华丽大赛的\n服务前台。$"

LilycoveCity_ContestLobby_Text_ContestReception::
   .string "你好！\p这里是宝可梦华丽大赛的\n服务前台。$"

@ Unused
LilycoveCity_ContestLobby_Text_CounterOnlyFor4PlayerContests::
   .string "你好！\p这里是为4名选手\n比赛准备的服务前台。$"

LilycoveCity_ContestLobby_Text_EnterContest1::
   .string "你想让你的宝可梦\n参加我们的华丽大赛吗？$"

LilycoveCity_ContestLobby_Text_WhichTopic1::
   .string "哪方面的比赛呢？$"

LilycoveCity_ContestLobby_Text_ExplainContests::
   .string "4位参赛选手拿出一只\n宝可梦进行评比。\p华丽大赛分为\n第一场和第二场展示。\p第一场评判是\n由观众的喜爱程度决定的。\p第二场评判的成绩是取决于\n宝可梦的动作的。\p你就应该计划好\n你的宝可梦的动作\l以获得更高的评价。\l第一场和第二场的成绩最后\n加起来成为总成绩。\p总成绩最高的宝可梦\n就是比赛的优胜者。$"

LilycoveCity_ContestLobby_Text_ExplainContestTypes::
   .string "一共有5个分组的比赛。\p帅气、美丽、可爱、\n聪明和强壮。\p为自己的宝可梦选择一个\n合适的分组吧。$"

LilycoveCity_ContestLobby_Text_ExplainContestRanks::
   .string "华丽大赛一共有4个\n不同的组别\p普通，超级，专家和大师\n4个组别。\p在普通组的比赛中任何一只\n宝可梦都可以参加。\p获得普通组胜利的宝可梦\n就获得了参加同一类型的\l超级组的比赛的资格\p同样的，获得超级组比赛胜利的\n就能参加专家组的比赛，\l专家组比赛胜利的能进入下一个等级\l大师组的比赛。\p所有的宝可梦训练师都希望自己的\n宝可梦获得大师组比赛\l的胜利。$"

LilycoveCity_ContestLobby_Text_EnterWhichRank::
   .string "你想参加哪个等级的比赛呢？$"

LilycoveCity_ContestLobby_Text_EnterWhichContest1::
   .string "你想参加哪个项目的比赛呢？$"

LilycoveCity_ContestLobby_Text_EnterWhichPokemon1::
   .string "你参加比赛的宝可梦是？$"

LilycoveCity_ContestLobby_Text_MonNotQualifiedForRank::
   .string "非常抱歉，你的宝可梦\n还没有资格参加\l这个等级的比赛…$"

LilycoveCity_ContestLobby_Text_EggCannotTakePart::
   .string "非常抱歉，宝可梦蛋是\n不能参加比赛的。$"

LilycoveCity_ContestLobby_Text_MonInNoConditionForContest::
   .string "还够资格参加这个等级的\l比赛…$"

LilycoveCity_ContestLobby_Text_AlreadyWonEnterAnyway::
   .string "这个缎带…\p你的宝可梦似乎已经获得了\n这个等级的缎带？\p你还想参加这个等级\n的比赛吗？$"

LilycoveCity_ContestLobby_Text_ConfirmContestMon::
   .string "那是你参加比赛的宝可梦吗？$"

LilycoveCity_ContestLobby_Text_YourMonIsEntryNum4::
   .string "好的你的宝可梦\n可以参加比赛了。\p你的宝可梦是第四位。\n比赛马上就开始了。$"

LilycoveCity_ContestLobby_Text_ComeThroughHere::
   .string "请这边走。\n祝你好运！$"

LilycoveCity_ContestLobby_Text_PokemonWonWeHavePrize::
   .string "恭喜！你的宝可梦\n获得了比赛的胜利！\p你的奖章在这边。\n请这边走！$"

LilycoveCity_ContestLobby_Text_ComeBackForPrizeLater::
   .string "请过会再来领取\n你的奖章。$"

ContestHall_Text_GettingStartedParticipantsAsFollows::
   .string "主持：你好！4人参加的华丽大赛\n马上就开始了\l{STR_VAR_2}！\p参加比赛是选手和他们的宠物为\n下列：$"

ContestHall_Text_GettingStartedParticipantsAsFollowsLink::
   .string "主持：你好！4人参加的华丽大赛\n马上就开始了\l{STR_VAR_2}！\p参加比赛是选手和他们的宠物为\n下列：$"

ContestHall_Text_EntryXTrainersMon::
   .string "主持：第{STR_VAR_2}号！\n{STR_VAR_1}的{STR_VAR_3}！$"

ContestHall_Text_SeenContestantsAudienceWillVote::
   .string "主持：4位参赛选手我们已经\n接受过了。\p现在开始进行初级评定！\p观众会给他们最喜欢的\n宝可梦投票。\p那么投票\n开始吧！$"

ContestHall_Text_VotingUnderWay::
   .string "投票进行中…$"

ContestHall_Text_VotingCompleteLetsAppeal::
   .string "投票结束了！\p投票结束后，\n我们开始进行中级评定\p接下来就大家最期待的\n表演阶段了！\p参赛选手们会跟我们\n带来怎么绚烂夺目的表演呢！\p就让我们一起\n拭目以待吧！$"

ContestHall_Text_ThatsItForJudging::
   .string "主持：比赛开始！$"

ContestHall_Text_ThankYouForAppeals::
   .string "感谢你为大家带来了\n如此出色的表演！\p这就是最终的结果！\n感谢你的努力！$"

ContestHall_Text_JudgeLooksReady::
   .string "现在所有准备\n工作已经结束了。\p裁判们看来要开始\n宣布结果了！$"

ContestHall_Text_WeWillNowDeclareWinner::
   .string "评委：现在我们就要开始宣布冠军了！$"

ContestHall_Text_CongratsTrainerXandMon::
   .string "主持：第{STR_VAR_2}！\p{STR_VAR_3}和{STR_VAR_1}，\n恭喜你！$"

ContestHall_Text_CongratsPleaseCompeteAgain::
   .string "主持：恭喜你！\n欢迎下次再来参加！$"

ContestHall_Text_AcceptYourPrize::
   .string "主持：给你！\n你的奖章！$"

ContestHall_Text_ConferRibbonAsPrize::
   .string "这个缎带就做为你的\n奖章吧！$"

ContestHall_Text_ReceivedRibbon::
   .string "{PLAYER}得到了缎带。$"

ContestHall_Text_PutRibbonOnMon::
   .string "{PLAYER}带上了缎带\n{STR_VAR_1}。$"

ContestHall_Text_PickUpPrizeAtCounterLater::
   .string "请稍后到前台来\n拿取奖品。\l欢迎下次再参加比赛！$"

@ Unused
ContestHall_Text_OnlyRegister4Players::
   .string "我只登记了4个选手\n参加比赛。\p如果另外3个选手连接过来\n所有4人将进入同一场比赛。\p你想加入吗？$"

LilycoveCity_ContestLobby_Text_ProgressWillBeSaved::
   .string "在开始比赛之前，\n系统将会进行记录。$"

LilycoveCity_ContestLobby_Text_ParticipateAnotherTime::
   .string "希望你下次还能参加\n比赛。$"

@ Unused
LilycoveCity_ContestLobby_Text_EnterContest2::
   .string "你想参加比赛吗？$"

@ Unused
LilycoveCity_ContestLobby_Text_Explain4PlayerContest::
   .string "当4个选手准备完毕，通过\n通信线进行连接，\l然后在我这里进行登记。\p请叫你的对手们\n选择同一个比赛。\p比赛会在所有选手登记进入后\n开启。\p之后，正常的比赛规则\n就会启动。$"

@ Unused
LilycoveCity_ContestLobby_Text_EnterWhichContest2::
   .string "你想参加哪个比赛？$"

@ Unused
LilycoveCity_ContestLobby_Text_EnterWhichPokemon2::
   .string "要让哪只宝可梦参加？$"

LilycoveCity_ContestLobby_Text_Transmitting::
   .string "传输中…$"

LilycoveCity_ContestLobby_Text_TransmissionError::
   .string "传输错误…$"

LilycoveCity_ContestLobby_Text_PlayersChoseDifferentContest::
   .string "你可能选择了和别人不一样的\n比赛。$"

LilycoveCity_ContestLobby_Text_PlayersMadeDifferentChoice::
   .string "你可能和其他选手的\n选择一样。$"

LilycoveCity_ContestLobby_Text_PleaseWaitBButtonCancel::
   .string "请等待。\n… … B键：取消$"

@ Unused
LilycoveCity_ContestLobby_Text_ParticipateAnotherTime2::
   .string "希望你下次\n再来参加。$"

@ Unused
LilycoveCity_ContestLobby_Text_TransmissionErrorTryAgain::
   .string "传输错误。\n请重试。$"

LilycoveCity_ContestLobby_Text_YourMonIsEntryNumX::
   .string "你的宝可梦\n可以参加比赛。\p你的编号是{STR_VAR_2}。$"

LilycoveCity_ContestLobby_Text_ContestBeginShortly::
   .string "比赛马上就要开始了。$"

LilycoveCity_ContestLobby_Text_LinkContestReception::
   .string "欢迎！这里是宝可梦华丽大赛\n通信服务前台。\p你可以和你的朋友们\n进行联机比赛。$"

LilycoveCity_ContestLobby_Text_WhichTopic2::
   .string "你喜欢哪个主题？$"

LilycoveCity_ContestLobby_Text_EnterContest3::
   .string "你想参加比赛吗？$"

LilycoveCity_ContestLobby_Text_EnterWhichContest3::
   .string "你想参加哪个方面的比赛呢？$"

LilycoveCity_ContestLobby_Text_MonInNoCondition2::
   .string "还够资格参加这个等级的\l比赛…$"

LilycoveCity_ContestLobby_Text_EggCannotTakePart2::
   .string "很抱歉你的宠物蛋是不\n能参加比赛。$"

LilycoveCity_ContestLobby_Text_EnterWhichPokemon3::
   .string "你想让哪只宝可梦参加？$"

LilycoveCity_ContestLobby_Text_PleaseDecideLinkLeader::
   .string "请选择你们中的谁\n是队长。\p其他人就只能选择\n“加入小组。”$"

LilycoveCity_ContestLobby_Text_PlayerAt4PCounterUseGMode::
   .string "最少有一个人参加\n这次的联机比赛。\p必须四个人使用\nGBA通信线。\p当4个人都已经准备好的时候，\n选择G-模式 (全球模式)，\l接着就开始了。$"

LilycoveCity_ContestLobby_Text_ExplainLinkContest::
   .string "这次的比赛是\n供两到四个人使用无线通信器\l或GBA连接线进行的。\p参加者先要选择他们所\n想要参加的模式。\p这有两种不同的模式。\pE模式(绿宝石模式)是对于\n两到四个人都使用了 \l宝可梦绿宝石卡带。\pG-模式(全球模式)只能使用于\n4个人同时都有绿宝石\l红宝石或蓝宝石游戏卡。\p4个人必须得决定他们\n选择的模式。\p一旦4个人选定了\n相同的赛事，\l注册就会结束了。\p在那以后比赛\n就会像往常那样开始了。$"

LilycoveCity_ContestLobby_Text_ExplainEMode::
   .string "在E模式(绿宝石模式)，\n两到四个人可以进行联机的\l华丽大赛，而且每个人都需要\l一张绿宝石的卡带。\p玩家们必须使用无线通信器\n或者是GBA联机\l线进行联机。\p如果人数少于四人，\n那么在大厅里的训练师就会\l加入到比赛中。\p要注意的是使用红宝石\n和蓝宝石的人不能使用E模式。$"

LilycoveCity_ContestLobby_Text_ExplainGMode::
   .string "G模式(全球模式)只有四个\n使用GBA连机线的人\l才能使用。\p每个人都必须要有\n绿宝石、红宝石、蓝宝石中的任意一张卡。\p比赛将在每个人选择了G模式\n后，或者是有连接器\l(红宝石、蓝宝石)\l。$"

LilycoveCity_ContestLobby_Text_NoWirelessAdapterInGMode::
   .string "非常抱歉。\pG模式不能通过无线\n通信器连接。\p请选择E模式或\n使用GBA通信线一次。$"

LilycoveCity_ContestLobby_Text_WhichContestMode::
   .string "你想参加哪个\n模式呢？$"

ContestHall_Text_GettingStartedWireless::
   .string "播音：你好啊！4只宝可梦的\n华丽大赛马上就要开始了。\l{STR_VAR_2}！$"

ContestHall_Text_ParticipantsAsFollows::
   .string "参加比赛的宝可梦有\n下面的几只：$"

ContestHall_Text_WeveSeenContestants::
   .string "播音：我们刚才看到了参加\n比赛的4只宝可梦。\p现在是大众评审阶段！$"

ContestHall_Text_AudienceWillVote::
   .string "观众马上开始给他们\n最喜欢的宝可梦投票了。$"

ContestHall_Text_LetVotingBegin::
   .string "OK，\n就让投票开始吧！$"

ContestHall_Text_VotingComplete::
   .string "投票结束了！\p让我们开始中级评判吧！$"

ContestHall_Text_SecondStageOfJudging::
   .string "接下来开始的就是\n大家期待已久的中级评判了！\p那些另人眼花缭乱的\n动作总是震惊着我们！$"

ContestHall_Text_LetsAppeal::
   .string "看看他们的热情多高啊！\n开始行动了！$"
