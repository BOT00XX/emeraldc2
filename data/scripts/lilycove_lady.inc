.set LOCALID_LILYCOVE_LADY, 4
.set LOCALID_LADYS_MON, 5

LilycoveCity_PokemonCenter_1F_EventScript_LilycoveLady::
    special Script_GetLilycoveLadyId
    switch VAR_RESULT
    case LILYCOVE_LADY_QUIZ, LilycoveCity_PokemonCenter_1F_EventScript_QuizLady
    case LILYCOVE_LADY_FAVOR, LilycoveCity_PokemonCenter_1F_EventScript_FavorLady
    case LILYCOVE_LADY_CONTEST, LilycoveCity_PokemonCenter_1F_EventScript_ContestLady
    end

LilycoveCity_PokemonCenter_1F_EventScript_FavorLady::
    lock
    faceplayer
    msgbox LilycoveCity_PokemonCenter_1F_Text_ImTheFavorLady, MSGBOX_DEFAULT
    specialvar VAR_RESULT, GetFavorLadyState
    compare VAR_RESULT, LILYCOVE_LADY_STATE_READY
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyReady
    compare VAR_RESULT, LILYCOVE_LADY_STATE_COMPLETED
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyCompleted
    compare VAR_RESULT, LILYCOVE_LADY_STATE_PRIZE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyPrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyCompleted::
    msgbox LilycoveCity_PokemonCenter_1F_Text_ThankYouForLastTime, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyReady::
    special BufferFavorLadyRequest
    msgbox LilycoveCity_PokemonCenter_1F_Text_ObsessedWithThing, MSGBOX_DEFAULT
    specialvar VAR_RESULT, HasAnotherPlayerGivenFavorLadyItem
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_RequestItem
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_TellAboutPlayersItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_TellAboutPlayersItem::
    special BufferFavorLadyItemName
    special BufferFavorLadyPlayerName
    specialvar VAR_RESULT, DidFavorLadyLikeItem
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveBadThing
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveGreatThing
    end

LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveBadThing::
    msgbox LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeBadThing, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_RequestItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_PlayerGaveGreatThing::
    msgbox LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeGreatThing, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_RequestItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_RequestItem::
    msgbox LilycoveCity_PokemonCenter_1F_Text_WillYouShareThing, MSGBOX_YESNO
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineFavor
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AcceptFavor
    end

LilycoveCity_PokemonCenter_1F_EventScript_DeclineFavor::
    msgbox LilycoveCity_PokemonCenter_1F_Text_IsThatSoGoodbye, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_AcceptFavor::
    msgbox LilycoveCity_PokemonCenter_1F_Text_WhatWillYouGiveMe, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_ChooseFavorItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_ChooseFavorItem::
    fadescreen FADE_TO_BLACK
    setvar VAR_RESULT, 0
    special Script_FavorLadyOpenBagMenu
    waitstate
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChooseFavorItem
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GiveFavorItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChooseFavorItem::
    msgbox LilycoveCity_PokemonCenter_1F_Text_NotWillingToShare, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineFavor
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ChooseFavorItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_GiveFavorItem::
    specialvar VAR_RESULT, Script_DoesFavorLadyLikeItem
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DidntLikeFavorItem
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_CheckLovedItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_DidntLikeFavorItem::
    special BufferFavorLadyRequest
    msgbox LilycoveCity_PokemonCenter_1F_Text_IllTryToCherishIt, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_CheckLovedItem::
    specialvar VAR_RESULT, IsFavorLadyThresholdMet
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_LikedFavorItem
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_LovedFavorItem
    end

LilycoveCity_PokemonCenter_1F_EventScript_LikedFavorItem::
    special BufferFavorLadyRequest
    msgbox LilycoveCity_PokemonCenter_1F_Text_IWillCherishThis, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_LovedFavorItem::
    special BufferFavorLadyRequest
    msgbox LilycoveCity_PokemonCenter_1F_Text_IWillTreasureThis, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyPrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_FavorLadyPrize::
    setvar VAR_0x8004, 0
    specialvar VAR_0x8004, FavorLadyGetPrize
    msgbox LilycoveCity_PokemonCenter_1F_Text_IllGiveYouThisInReturn, MSGBOX_DEFAULT
    giveitem VAR_0x8004
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_NoRoomForFavorPrize
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ReceivedFavorPrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_NoRoomForFavorPrize::
    msgbox LilycoveCity_PokemonCenter_1F_Text_YouDontHaveSpaceForIt, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_ReceivedFavorPrize::
    special SetFavorLadyState_Complete
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_QuizLady::
    lock
    faceplayer
    msgbox LilycoveCity_PokemonCenter_1F_Text_ImTheQuizLady, MSGBOX_DEFAULT
    specialvar VAR_RESULT, GetQuizLadyState
    compare VAR_RESULT, LILYCOVE_LADY_STATE_READY
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_HasQuiz
    compare VAR_RESULT, LILYCOVE_LADY_STATE_COMPLETED
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_CheckMadeQuiz
    compare VAR_RESULT, LILYCOVE_LADY_STATE_PRIZE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ReadyGivePrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_HasQuiz::
    specialvar VAR_RESULT, GetQuizAuthor
    compare VAR_RESULT, QUIZ_AUTHOR_PLAYER
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_WaitingToTakeYourQuiz
    compare VAR_RESULT, QUIZ_AUTHOR_OTHER_PLAYER
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_PlayerQuizReady
    compare VAR_RESULT, QUIZ_AUTHOR_LADY
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_LadyQuizReady
    end

LilycoveCity_PokemonCenter_1F_EventScript_CheckMadeQuiz::
    specialvar VAR_RESULT, IsQuizLadyWaitingForChallenger
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_WaitingToTakeYourQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_WaitingToTakeYourQuiz::
    msgbox LilycoveCity_PokemonCenter_1F_Text_WaitingToTakeYourQuiz, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_PlayerQuizReady::
    msgbox LilycoveCity_PokemonCenter_1F_Text_WaitingForChallenger, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_AskTakeQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_LadyQuizReady::
    msgbox LilycoveCity_PokemonCenter_1F_Text_WaitingForChallenger, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_AskTakeQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskTakeQuiz::
    setvar VAR_0x8004, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_TakeQuizChallenge, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_TakeQuiz
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_DeclineQuiz::
    msgbox LilycoveCity_PokemonCenter_1F_Text_HowBoringBye, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_TakeQuiz::
    special ClearQuizLadyPlayerAnswer
    compare VAR_0x8004, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ShowQuestion
    compare VAR_0x8004, EASY_CHAT_TYPE_QUIZ_ANSWER
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GetAnswer

LilycoveCity_PokemonCenter_1F_EventScript_CheckQuizTakingState::
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskQuitQuiz
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_SubmitQuizResponse
    end

LilycoveCity_PokemonCenter_1F_EventScript_ShowQuestion::
    special QuizLadyShowQuizQuestion
    waitstate
    goto LilycoveCity_PokemonCenter_1F_EventScript_CheckQuizTakingState
    end

LilycoveCity_PokemonCenter_1F_EventScript_GetAnswer::
    special QuizLadyGetPlayerAnswer
    waitstate
    goto LilycoveCity_PokemonCenter_1F_EventScript_CheckQuizTakingState
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskQuitQuiz::
    msgbox LilycoveCity_PokemonCenter_1F_Text_YoureGoingToQuit, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_QuitTakingQuiz
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_TakeQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_QuitTakingQuiz::
    msgbox LilycoveCity_PokemonCenter_1F_Text_TakeTheQuizAnotherTime, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_SubmitQuizResponse::
    special SetQuizLadyState_Complete
    msgbox LilycoveCity_PokemonCenter_1F_Text_WaitForAnswer, MSGBOX_DEFAULT
    specialvar VAR_RESULT, IsQuizAnswerCorrect
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_IncorrectResponse
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_CorrectResponse
    end

LilycoveCity_PokemonCenter_1F_EventScript_CorrectResponse::
    playse SE_SUCCESS
    delay 10
    playse SE_SUCCESS
    msgbox LilycoveCity_PokemonCenter_1F_Text_YouGotItRight, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_ReadyGivePrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_IncorrectResponse::
    special BufferQuizCorrectAnswer
    special BufferQuizPrizeName
    playse SE_FAILURE
    delay 10
    playse SE_FAILURE
    msgbox LilycoveCity_PokemonCenter_1F_Text_WrongTheCorrectAnswerIs, MSGBOX_DEFAULT
    msgbox LilycoveCity_PokemonCenter_1F_Text_IGetToKeepPrize, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz
    end

@ VAR_RESULT is essentially ignored, both jumps are identical
LilycoveCity_PokemonCenter_1F_EventScript_ReadyGivePrize::
    specialvar VAR_RESULT, BufferQuizAuthorNameAndCheckIfLady
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GivePrize1
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GivePrize0
    end

LilycoveCity_PokemonCenter_1F_EventScript_GivePrize1::
    msgbox LilycoveCity_PokemonCenter_1F_Text_YouGotItRightYouveWonPersonsPrize, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_GivePrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_GivePrize0::
    msgbox LilycoveCity_PokemonCenter_1F_Text_YouGotItRightYouveWonPersonsPrize, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_GivePrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_GivePrize::
    setvar VAR_0x8005, 0
    special BufferQuizPrizeItem
    special SetQuizLadyState_Complete
    giveitem VAR_0x8005
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_NoSpaceForQuizPrize
    goto LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_NoSpaceForQuizPrize::
    msgbox LilycoveCity_PokemonCenter_1F_Text_YourBagIsFilledUp, MSGBOX_DEFAULT
    special SetQuizLadyState_GivePrize
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskMakeQuiz::
    msgbox LilycoveCity_PokemonCenter_1F_Text_MakeYourOwnQuiz, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_MakeQuiz
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz::
    special QuizLadyPickNewQuestion
    msgbox LilycoveCity_PokemonCenter_1F_Text_MaybeNextTime, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_MakeQuiz::
    msgbox LilycoveCity_PokemonCenter_1F_Text_PickYourPrize, MSGBOX_DEFAULT
LilycoveCity_PokemonCenter_1F_EventScript_PickPrize::
    fadescreen FADE_TO_BLACK
    setvar VAR_RESULT, 0
    special Script_QuizLadyOpenBagMenu
    waitstate
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChoosingPrize
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_WriteQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskQuitChoosingPrize::
    msgbox LilycoveCity_PokemonCenter_1F_Text_QuitChoosingPrize, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_PickPrize
    end

LilycoveCity_PokemonCenter_1F_EventScript_WriteQuiz::
    msgbox LilycoveCity_PokemonCenter_1F_Text_WriteYourQuiz, MSGBOX_DEFAULT
    special ClearQuizLadyQuestionAndAnswer
    special ClearQuizLadyPlayerAnswer
    setvar VAR_0x8004, EASY_CHAT_TYPE_QUIZ_QUESTION
LilycoveCity_PokemonCenter_1F_EventScript_WriteQuizQuestion::
    fadescreen FADE_TO_BLACK
    special QuizLadySetCustomQuestion
    waitstate
    compare VAR_RESULT, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskQuitWritingQuizQuestion
    goto LilycoveCity_PokemonCenter_1F_EventScript_FinishMakingQuiz
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskQuitWritingQuizQuestion::
    msgbox LilycoveCity_PokemonCenter_1F_Text_QuitWritingQuizQuestion, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineMakeQuiz
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_WriteQuizQuestion
    end

LilycoveCity_PokemonCenter_1F_EventScript_FinishMakingQuiz::
    special QuizLadyTakePrizeForCustomQuiz
    special QuizLadyRecordCustomQuizData
    special QuizLadySetWaitingForChallenger
    msgbox LilycoveCity_PokemonCenter_1F_Text_IllLookForAChallenger, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_ContestLady::
    lock
    faceplayer
    msgbox LilycoveCity_PokemonCenter_1F_Text_ImTheContestLady, MSGBOX_DEFAULT
    specialvar VAR_RESULT, HasPlayerGivenContestLadyPokeblock
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_NotGivenPokeblock
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GivenPokeblock
    end

@ Redundant with above script, VAR_RESULT will always be FALSE here
LilycoveCity_PokemonCenter_1F_EventScript_NotGivenPokeblock::
    specialvar VAR_RESULT, ShouldContestLadyShowGoOnAir
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskForPokeblock
    compare VAR_RESULT, TRUE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_GivenPokeblock
    end

LilycoveCity_PokemonCenter_1F_EventScript_GivenPokeblock::
    msgbox LilycoveCity_PokemonCenter_1F_Text_ThankForPokeblock, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskForPokeblock::
    special Script_BufferContestLadyCategoryAndMonName
    msgbox LilycoveCity_PokemonCenter_1F_Text_MyFriendDisplaysQuality, MSGBOX_DEFAULT
    checkitem ITEM_POKEBLOCK_CASE, 1
    compare VAR_RESULT, FALSE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_NoPokeblockCase
    msgbox LilycoveCity_PokemonCenter_1F_Text_AskingForOnePokeblock, MSGBOX_YESNO
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineGivePokeblock
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ChoosePokeblock
    end

LilycoveCity_PokemonCenter_1F_EventScript_DeclineGivePokeblock::
    msgbox LilycoveCity_PokemonCenter_1F_Text_WhatACheapskate, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_ChoosePokeblock::
    fadescreen FADE_TO_BLACK
    special OpenPokeblockCaseForContestLady
    waitstate
    compare VAR_RESULT, 0xFFFF
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AskQuitGivingPokeblock
    compare VAR_RESULT, 0xFFFF
    goto_if_ne LilycoveCity_PokemonCenter_1F_EventScript_GivePokeblock
    end

LilycoveCity_PokemonCenter_1F_EventScript_AskQuitGivingPokeblock::
    msgbox LilycoveCity_PokemonCenter_1F_Text_ICantHaveOnePokeblock, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_DeclineGivePokeblock
    compare VAR_RESULT, NO
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_ChoosePokeblock
    end

LilycoveCity_PokemonCenter_1F_EventScript_GivePokeblock::
    msgbox LilycoveCity_PokemonCenter_1F_Text_IllUseYourPokeblock, MSGBOX_DEFAULT
    special SetContestLadyGivenPokeblock
    special GetContestLadyMonSpecies
    goto LilycoveCity_PokemonCenter_1F_EventScript_FeedPokeblock
    end

@ VAR_0x8004 here is the return value from GivePokeblockToContestLady
LilycoveCity_PokemonCenter_1F_EventScript_FeedPokeblock::
    applymovement LOCALID_LILYCOVE_LADY, LilycoveCity_PokemonCenter_1F_Movement_LadyFaceMon
    waitmovement 0
    delay 60
    applymovement LOCALID_LADYS_MON, LilycoveCity_PokemonCenter_1F_Movement_MonFaceLady
    waitmovement 0
    delay 60
    waitse
    playmoncry VAR_0x8005, 0
    delay 120
    waitmoncry
    compare VAR_0x8004, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_MonEnjoyPokeblock
    goto LilycoveCity_PokemonCenter_1F_EventScript_FinishFeedPokeblock
    end

@ VAR_0x8004 here is the return value from GivePokeblockToContestLady
LilycoveCity_PokemonCenter_1F_EventScript_MonEnjoyPokeblock::
    applymovement LOCALID_LADYS_MON, LilycoveCity_PokemonCenter_1F_Movement_MonJump
    waitmovement 0
    delay 60
LilycoveCity_PokemonCenter_1F_EventScript_FinishFeedPokeblock::
    applymovement LOCALID_LILYCOVE_LADY, LilycoveCity_PokemonCenter_1F_Movement_LadyFacePlayer
    waitmovement 0
    delay 60
    compare VAR_0x8004, 0
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_MonDislikedPokeblock
    compare VAR_0x8004, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_MonLikedPokeblock
    end

LilycoveCity_PokemonCenter_1F_EventScript_MonDislikedPokeblock::
    msgbox LilycoveCity_PokemonCenter_1F_Text_NoChangeThanks, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_CheckAirContestLadyShow
    end

LilycoveCity_PokemonCenter_1F_EventScript_MonLikedPokeblock::
    special Script_BufferContestLadyCategoryAndMonName
    msgbox LilycoveCity_PokemonCenter_1F_Text_ReallyImprovedThanks, MSGBOX_DEFAULT
    goto LilycoveCity_PokemonCenter_1F_EventScript_CheckAirContestLadyShow
    end

LilycoveCity_PokemonCenter_1F_EventScript_CheckAirContestLadyShow::
    specialvar VAR_RESULT, ShouldContestLadyShowGoOnAir
    compare VAR_RESULT, 1
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_AirContestLadyShow
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_AirContestLadyShow::
    msgbox LilycoveCity_PokemonCenter_1F_Text_ReadyToEnterContests, MSGBOX_DEFAULT
    special PutLilycoveContestLadyShowOnTheAir
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_NoPokeblockCase::
    msgbox LilycoveCity_PokemonCenter_1F_Text_DontHaveAPokeblockCase, MSGBOX_DEFAULT
    release
    end

LilycoveCity_PokemonCenter_1F_Movement_LadyFaceMon:
    face_right
    delay_8
    step_end

LilycoveCity_PokemonCenter_1F_Movement_MonFaceLady:
    face_left
    delay_8
    step_end

@ Unused
LilycoveCity_PokemonCenter_1F_Movement_MonFaceDown:
    face_down
    step_end

LilycoveCity_PokemonCenter_1F_Movement_LadyFacePlayer:
    face_player
    step_end

LilycoveCity_PokemonCenter_1F_Movement_MonJump:
    disable_jump_landing_ground_effect
    jump_in_place_left
    disable_jump_landing_ground_effect
    jump_in_place_left
    step_end

LilycoveCity_PokemonCenter_1F_EventScript_ContestLadyMon::
    specialvar VAR_RESULT, GetContestLadyCategory
    special Script_BufferContestLadyCategoryAndMonName
    special GetContestLadyMonSpecies
    compare VAR_RESULT, CONTEST_CATEGORY_COOL
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_Zigzagoon
    compare VAR_RESULT, CONTEST_CATEGORY_BEAUTY
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_Skitty
    compare VAR_RESULT, CONTEST_CATEGORY_CUTE
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_Poochyena
    compare VAR_RESULT, CONTEST_CATEGORY_SMART
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_Kecleon
    compare VAR_RESULT, CONTEST_CATEGORY_TOUGH
    goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_Pikachu
    end

LilycoveCity_PokemonCenter_1F_EventScript_Zigzagoon::
    lock
    faceplayer
    waitse
    playmoncry VAR_0x8005, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_Zigzagoon, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_Skitty::
    lock
    faceplayer
    waitse
    playmoncry VAR_0x8005, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_Skitty, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_Poochyena::
    lock
    faceplayer
    waitse
    playmoncry VAR_0x8005, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_Poochyena, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_Kecleon::
    lock
    faceplayer
    waitse
    playmoncry VAR_0x8005, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_Kecleon, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_PokemonCenter_1F_EventScript_Pikachu::
    lock
    faceplayer
    waitse
    playmoncry VAR_0x8005, 0
    msgbox LilycoveCity_PokemonCenter_1F_Text_Pikachu, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_PokemonCenter_1F_Text_ImTheFavorLady::
   .string "我是喜好女士…$"

LilycoveCity_PokemonCenter_1F_Text_ObsessedWithThing::
   .string "最近我一直\n希望能{STR_VAR_1}…$"

LilycoveCity_PokemonCenter_1F_Text_ThankYouForLastTime::
   .string "啊…\n之前谢谢你了…$"

LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeBadThing::
   .string "以前，大概是{STR_VAR_3}…\p{STR_VAR_3}给了我{STR_VAR_2}，\n说它{STR_VAR_1}，\p但那根本不{STR_VAR_1}，\n完全不。$"

LilycoveCity_PokemonCenter_1F_Text_PlayerGaveMeGreatThing::
   .string "以前，{STR_VAR_3}给了我\n非常{STR_VAR_1}的{STR_VAR_2}，\p现在我还在珍藏着。$"

LilycoveCity_PokemonCenter_1F_Text_WillYouShareThing::
   .string "听着，如果你也有什么\n{STR_VAR_1}的东西，\l能送给我吗？$"

LilycoveCity_PokemonCenter_1F_Text_WhatWillYouGiveMe::
   .string "…真的？\n你要给我什么？$"

LilycoveCity_PokemonCenter_1F_Text_IsThatSoGoodbye::
   .string "是吗？\n那么再见吧…$"

LilycoveCity_PokemonCenter_1F_Text_NotWillingToShare::
   .string "哎…\n你不愿意给啊。$"

LilycoveCity_PokemonCenter_1F_Text_IllTryToCherishIt::
   .string "哦？\n那个{STR_VAR_2}{STR_VAR_1}吗？\p…哎，真的吗？\p谢谢你，我会保存好的…$"

LilycoveCity_PokemonCenter_1F_Text_IWillCherishThis::
   .string "啊…\p真的是非常{STR_VAR_1}的\n{STR_VAR_2}…\p真好啊，\n好象做梦一样…\p谢谢你…\n我会珍惜的…$"

LilycoveCity_PokemonCenter_1F_Text_IWillTreasureThis::
   .string "…啊，啊，啊…\p多不可思议啊！\n真的非常{STR_VAR_1}！\p我从来都不知道{STR_VAR_2}\n会这么{STR_VAR_1}！\p谢谢，谢谢！\n我会珍藏一辈子的！$"

LilycoveCity_PokemonCenter_1F_Text_IllGiveYouThisInReturn::
   .string "你给了我这么好的礼物，\n这个就当作我的回礼吧，\p希望你也能好好保存…$"

LilycoveCity_PokemonCenter_1F_Text_YouDontHaveSpaceForIt::
   .string "哎，你的背包没空间\n装下这个了啊。\p整理好之后\n再来找我吧…$"

LilycoveCity_PokemonCenter_1F_Text_ImTheQuizLady::
   .string "我是谜题女士！\n我喜欢谜题！$"

LilycoveCity_PokemonCenter_1F_Text_WaitingToTakeYourQuiz::
   .string "哦？\p我正在为你出的谜题\n寻找挑战者，\p下次再聊吧？$"

LilycoveCity_PokemonCenter_1F_Text_WaitingForChallenger::
   .string "我正在寻找愿意挑战\n{STR_VAR_1}的谜题的人！$"

LilycoveCity_PokemonCenter_1F_Text_TakeQuizChallenge::
   .string "你能解出来的话，\n就会得到精美的奖品！\p想要挑战吗？$"

LilycoveCity_PokemonCenter_1F_Text_WaitForAnswer::
   .string "… … … … … …\n… … … … … …$"

LilycoveCity_PokemonCenter_1F_Text_HowBoringBye::
   .string "啊，真遗憾！\n再见！$"

LilycoveCity_PokemonCenter_1F_Text_YoureGoingToQuit::
   .string "啊啊！\n你要退出吗？$"

LilycoveCity_PokemonCenter_1F_Text_TakeTheQuizAnotherTime::
   .string "以后再来挑战吧！$"

LilycoveCity_PokemonCenter_1F_Text_YouGotItRight::
   .string "真惊讶！你答对了！\n真是敏锐的人啊！$"

LilycoveCity_PokemonCenter_1F_Text_YouGotItRightYouveWonPersonsPrize::
   .string "恭喜！你解开了谜题！\p这是{STR_VAR_1}提供的奖品！$"

@ Unused
LilycoveCity_PokemonCenter_1F_Text_XReceivedOneY::
   .string "{STR_VAR_1}得到了\n{STR_VAR_2}！$"

LilycoveCity_PokemonCenter_1F_Text_YourBagIsFilledUp::
   .string "哎？你的背包满了！\n有空间的时候再来吧。$"

LilycoveCity_PokemonCenter_1F_Text_WrongTheCorrectAnswerIs::
   .string "唔…错了。\n正确答案应该是“{STR_VAR_3}”！$"

LilycoveCity_PokemonCenter_1F_Text_IGetToKeepPrize::
   .string "真遗憾，\p奖品{STR_VAR_1}我只好保留了！$"

LilycoveCity_PokemonCenter_1F_Text_MakeYourOwnQuiz::
   .string "那个，那个，\n你也想出题吗？$"

LilycoveCity_PokemonCenter_1F_Text_MaybeNextTime::
   .string "哦，知道了…\n那，下次好了！$"

LilycoveCity_PokemonCenter_1F_Text_PickYourPrize::
   .string "好的，首先你要选择一样\n奖给回答正确的优胜者的礼物。\p但要当心，如果挑战者\n回答错了，\l我就会保留奖品！$"

LilycoveCity_PokemonCenter_1F_Text_QuitChoosingPrize::
   .string "不选择奖品的话\n就不能出题了，\p你要放弃吗？$"

LilycoveCity_PokemonCenter_1F_Text_WriteYourQuiz::
   .string "啊，真棒！\n真不错的奖品！\p下面，你需要写下你的\n问题和答案。$"

LilycoveCity_PokemonCenter_1F_Text_QuitWritingQuizQuestion::
   .string "不想出题了吗？$"

@ Unused
LilycoveCity_PokemonCenter_1F_Text_QuitWritingQuizAnswer::
   .string "你要退出\n答案选择吗？$"

LilycoveCity_PokemonCenter_1F_Text_IllLookForAChallenger::
   .string "好的！\n不错的问题。\p我这就去找\n愿意回答你的问题的挑战者。$"

LilycoveCity_PokemonCenter_1F_Text_ImTheContestLady::
   .string "我是选美女士！\n我非常喜欢华丽大赛！$"

LilycoveCity_PokemonCenter_1F_Text_ThankForPokeblock::
   .string "谢谢你的能量方块！$"

LilycoveCity_PokemonCenter_1F_Text_MyFriendDisplaysQuality::
   .string "这是我的伙伴{STR_VAR_1}！\n它就是{STR_VAR_2}的典型！\p但我认为它的表现\n还会更{STR_VAR_2}！$"

LilycoveCity_PokemonCenter_1F_Text_DontHaveAPokeblockCase::
   .string "能帮我个忙吗？\p给我个能量方块可以吗？\n我只想要一个而已！\p…哎，等等…\n你没有能量方块盒？\l真可惜，那么下次再说吧！$"

LilycoveCity_PokemonCenter_1F_Text_AskingForOnePokeblock::
   .string "能帮我个忙吗？\p给我个能量方块可以吗？\n我只想要一个而已！$"

LilycoveCity_PokemonCenter_1F_Text_ICantHaveOnePokeblock::
   .string "啊啊啊！\n一个能量方块都不给吗？$"

LilycoveCity_PokemonCenter_1F_Text_WhatACheapskate::
   .string "嘁！小气鬼！$"

LilycoveCity_PokemonCenter_1F_Text_IllUseYourPokeblock::
   .string "耶！谢谢！\n马上就用它去喂我的宝可梦！$"

LilycoveCity_PokemonCenter_1F_Text_NoChangeThanks::
   .string "…看上去什么变化\n也没有啊…\p唔…\p啊，还是谢谢你！$"

LilycoveCity_PokemonCenter_1F_Text_ReallyImprovedThanks::
   .string "哦，耶！\n它很高兴啊！\p它{STR_VAR_1}的{STR_VAR_2}\n肯定提升了！\p非常感谢！$"

LilycoveCity_PokemonCenter_1F_Text_ReadyToEnterContests::
   .string "唔…\p看来我们应该可以\n参加华丽大赛了。\p如果你在哪儿看到我们的话，\n请为我们加油吧。$"

LilycoveCity_PokemonCenter_1F_Text_Zigzagoon::
   .string "{STR_VAR_1}：咕～咕呜！$"

LilycoveCity_PokemonCenter_1F_Text_Kecleon::
   .string "{STR_VAR_1}：唧唧，唧唧！$"

LilycoveCity_PokemonCenter_1F_Text_Poochyena::
   .string "{STR_VAR_1}：汪—呜…$"

LilycoveCity_PokemonCenter_1F_Text_Pikachu::
   .string "{STR_VAR_1}：皮～卡！$"

LilycoveCity_PokemonCenter_1F_Text_Skitty::
   .string "{STR_VAR_1}：呜—喵～$"
