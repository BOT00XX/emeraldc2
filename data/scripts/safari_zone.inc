SafariZone_EventScript_OutOfBallsMidBattle::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	setwarp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 255, 2, 5
	end

SafariZone_EventScript_Exit::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	warp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 255, 2, 5
	waitstate
	end

SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SafariZone_EventScript_Retire
	releaseall
	end

SafariZone_EventScript_Retire::
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

EventScript_PokeBlockFeeder::
	lockall
	special GetPokeblockFeederInFront
	compare VAR_RESULT, 0xFFFF
	goto_if_ne SafariZone_EventScript_PokeblockPresent
	msgbox SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

SafariZone_EventScript_ChoosePokeblock::
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	waitstate
	compare VAR_RESULT, 0xFFFF
	goto_if_ne SafariZone_EventScript_PokeblockPlaced
	end

SafariZone_EventScript_PokeblockPlaced::
	message SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockPresent::
	message SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_Text_WouldYouLikeToExit::
   .string "你现在就要退出\n野生原野区吗？$"

SafariZone_Text_TimesUp::
   .string "叮-咚！时间到！\n原野区活动结束。$"

SafariZone_Text_OutOfBalls::
   .string "原野球没了，\n原野区活动结束。$"

SafariZone_Text_PlacePokeblockOnFeeder::
   .string "要在能量方块喂养器里面\n放进能量方块吗？$"

SafariZone_Text_PokeblockStillHere::
   .string "你之前放进去的{STR_VAR_1}\n还在里面。$"

SafariZone_Text_PokeblockWasPlaced::
   .string "把{STR_VAR_1}放进了\n能量方块喂养器里。$"

Route121_SafariZoneEntrance_Text_WelcomeToSafariZone::
   .string "欢迎来到野生原野区！\p在这里有许多丰缘地区\n难得一见的宝可梦，\p你可以观察这些野生宝可梦\n在自然栖息地的生活。\p另外，我们也欢迎\n宝可梦训练师的到来，\p你可以在这里捕捉\n你想要的宝可梦！\p祝你在野生原野区玩得愉快！$"

Route121_SafariZoneEntrance_Text_WelcomeFirstTime::
   .string "欢迎来到野生原野区！\n请问是第一次来这里吗？$"

Route121_SafariZoneEntrance_Text_ComeInAndEnjoy::
   .string "祝你在野生原野区玩得愉快！$"

Route121_SafariZoneEntrance_Text_FirstTimeInfo::
   .string "进入野生原野区以后，\n会给你30只原野球用来捕捉宝可梦，\p原野球用完或者你走了500步以后，\n原野区活动就结束了。\p祝你在野生原野区玩得愉快！$"

Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay::
   .string "欢迎来到野生原野区！\p花500$就可以尽情地捕捉宝可梦！\n你要进行原野区活动吗？$"

Route121_SafariZoneEntrance_Text_PlayAnotherTime::
   .string "好的，\n欢迎下次再来！$"

Route121_SafariZoneEntrance_Text_NotEnoughMoney::
   .string "抱歉，\n你带的钱不够。$"

Route121_SafariZoneEntrance_Text_ThatWillBe500Please::
   .string "请先付500。$"

Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls::
   .string "请收好你的原野球。$"

Route121_SafariZoneEntrance_Text_Received30SafariBalls::
   .string "{PLAYER}得到30个原野球。$"

Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself::
   .string "游戏结束的时候你会收到通知，\n在那之前，请尽情地玩吧。\l野生的宝可梦们在等着你去发现！$"

Route121_SafariZoneEntrance_Text_PCIsFull::
   .string "很抱歉，\n你的电脑盒子满了。$"

Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase::
   .string "很抱歉，\n似乎你还没有能量方块盒。\p使用能量方块会使\n原野区活动变得更有趣的。\p拿到能量方块盒再来吧，\p你可以在水静市选美大厅\n索要到能量方块盒。$"

SafariZone_South_Text_StillHaveTimeExit::
   .string "你的时间还没有用完，\n现在就要离开野生原野区吗？$"

SafariZone_South_Text_EnjoyTheRestOfYourAdventure::
   .string "在剩下的时间里\n尽情享受野外冒险的乐趣吧！$"

SafariZone_South_Text_ExitEarlyThankYouForPlaying::
   .string "好的，现在我要收回\n你余下的原野球。\p谢谢你的光临，\n下次再见。$"

SafariZone_South_Text_GoodLuck::
   .string "祝你好运！\p需要什么帮助的话，\n就直接告诉我吧！$"

SafariZone_South_Text_Boy::
   .string "知道吗？如果在那个\p方方的箱子里放进能量方块，\n宝可梦就会聚集到那附近。$"

SafariZone_South_Text_Man::
   .string "我本来想走得更深一点的，\n但我忘记带自行车了。\p据说一些稀有的宝可梦\n生活在比较偏僻的地方。$"

SafariZone_Southwest_Text_Woman::
   .string "有的时候，宝可梦会无视\n我扔出去的能量方块。\p是不是宝可梦们对于食物\n也有不同的喜好呢？$"

SafariZone_Northwest_Text_Man::
   .string "呼…呼…\n我…终于到这儿了…不过…\p我已经累了…没力气\n去抓宝可梦了…$"

SafariZone_North_Text_Fisherman::
   .string "我需要找到一些丰缘地区\n所没有的水系宝可梦，\p你知道湖在哪儿吗？$"

SafariZone_North_Text_Man::
   .string "我要在这儿抓一大堆宝可梦，\n然后跟我的朋友们交换！$"

SafariZone_South_Text_Youngster::
   .string "我把能量方块放到了能量方块\n喂养器里，但它很快就消失了。\p一定是在我没注意的时候\n被宝可梦吃掉了。$"

Route121_SafariZoneEntrance_Text_TrainerTip::
   .string "野生原野区要领\p向野生宝可梦投掷能量方块，\n能够减少它们逃跑的可能性。$"

SafariZone_Southwest_Text_RestHouseSign::
   .string "“放松一下你疲惫的双脚吧”\n休息客栈$"

SafariZone_RestHouse_Text_Youngster::
   .string "我没有能量方块，\n但我还是抓到了很多宝可梦。\p先小心地接近，\n然后再扔出原野球，\l就有更大的可能性抓到它们。$"

SafariZone_RestHouse_Text_PsychicM::
   .string "如果使用能量方块，野生宝可梦\n就不会很快逃跑。\p而对于那些本来就不太容易逃跑的宝可梦，\n使用能量方块效果并不大。$"

SafariZone_RestHouse_Text_FatMan::
   .string "放在喂养器里的能量方块\n能够把宝可梦吸引来，\p我想有相似性格的宝可梦\n会被同一种能量方块吸引。$"

SafariZone_South_Text_AreaOffLimits1::
   .string "此处正在建设中，\n禁止入内。$"

SafariZone_Southeast_Text_ExpansionIsFinished::
   .string "野生原野区的扩建\n已经完工，\p希望你能喜欢。$"

SafariZone_South_Text_AreaOffLimits2::
   .string "此处正在建设中，\n禁止入内。$"

SafariZone_Southeast_Text_LittleGirl::
   .string "呀～嗬！这些宝可梦\n都是我从来没见过的！$"

SafariZone_Southeast_Text_FatMan::
   .string "这些宝可梦\n我还是第一次见到，\p而且我还可以抓这些\n稀有宝可梦！太棒了！$"

SafariZone_Southeast_Text_RichBoy::
   .string "这里的宝可梦好像\n是从丰缘外来的。$"

SafariZone_Northeast_Text_Boy::
   .string "我的原野球没剩几个了，\p我得好好考虑一下\n要抓什么样的宝可梦。$"

SafariZone_Northeast_Text_Woman::
   .string "据说有人在这附近发现过皮卡丘，\n究竟在哪儿呢？$"

SafariZone_Northeast_Text_Girl::
   .string "啊，真烦！\n我什么都没抓到！\p要是再抓不住什么的话\n我就不在这儿浪费钱了！$"
