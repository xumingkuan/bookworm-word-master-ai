#include "bookworm_ai_methods.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <set>
#include <time.h>
#define NDEBUG
#include <assert.h>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

extern bool debug_mode;

char scramble[NUM_SCRAMBLE][WORD_LEN + 1];

const char FIRST_GUESS[NUMC][WORD_LEN + 1] = {"tries","tales","tares","tries","alist","tires","tales","lares","trend","kales","snare","tares","nates","rates","arles","lares","tries","aides","plate","pares","train","tales","tares","xenic","lares","lenis"};
int first_guess[NUMC];

const int NUM_S_G = 243;  // 3^WORD_LEN
const char SECOND_GUESS[NUMC][NUM_S_G][WORD_LEN + 1] = {
{"blond","","blond","armor","","argot","mogul","","clomp","incog","","amity","","","","","","","aloin","","cumin","argil","","","acrid","","atrip","aland","","anted","armed","","armet","luged","","apter","adieu","","","ariel","","","","","","aimed","","","","","","aired","","","noble","","conge","argle","","arete","afore","","avert","anile","","axite","","","","afire","","","aggie","","","","","","aerie","","","gloam","","autos","arums","","","agars","","","adman","","adits","arias","","","amirs","","","","","antis","arris","","","airns","","airts","mulch","","antes","arles","","","aures","","","amies","","","","","","amies","","","aides","","","arles","","","","","","avens","","abets","areas","","","avers","","","","","","arias","","","","","","aegis","","","","","","","","","awash","","angst","arson","","artsy","","","","aviso","","agist","","","","","","","aspic","","","","","","","","astir","asked","","asset","","","","asker","","aster","","","","ariel","","","","","","","","","","","","","","","abuse","","","arose","","","","","","anise","","","arise","","arise","","","","aisle","","","","","","","",""},
{"cornu","","routh","gyron","","nitty","drink","","brant","bully","","","balmy","","","bylaw","","","drink","","blurt","baulk","","","drain","","bloat","drown","","beret","drank","","bated","","","","","","","baled","","","","","","bleed","","botel","babel","","","","","","irone","","begot","badge","","bathe","crank","","begat","belle","","","","","","belay","","","ruble","","blite","","","","merde","","blate","korun","","rutin","drink","","baths","wordy","","boats","kudos","","bolts","balms","","","bolas","","","coirs","","blots","bawls","","","blaws","","blats","orcin","","bites","korun","","bates","braes","","","biles","","","bales","","bales","biles","","","blues","","","korun","","bates","","","","genre","","beets","","","","demur","","beats","bells","","belts","balms","","","","","","blebs","","blets","","","","","","","bousy","","burst","basin","","","brash","","boast","","","","balsa","","","","","","blush","","","basal","","","","","blast","bused","","beset","based","","","","","","","","","baled","","","","","","","","","","","","","","","bouse","","besot","","","baste","","","beast","","","","","","","","","","","","blest","","","","blase","",""},
{"noily","","putto","lindy","","catty","plain","","coapt","loury","","","limbo","","carat","coria","","","prior","","croft","caird","","","kraal","","chart","blond","","covet","podgy","","cadet","","","","cured","","curet","carex","","caret","","","","proud","","cuter","pingo","","cater","","","","noily","","conte","glove","","","plead","","cheat","curie","","","carle","","carte","ceria","","","crepe","","chert","cadre","","","prank","","crate","plonk","","soils","flump","","cants","modal","","chats","blond","","","plunk","","carts","","","","crows","","","","","","brash","","","plonk","","cutes","punky","","cates","","","","cures","","","cares","","cares","cures","","","cries","","","punky","","cates","","","","welsh","","celts","","","","","","","","","","plunk","","carts","","","","cress","","","","","","","","","cissy","","","canso","","canst","clash","","coast","","","curst","","","","","","","crisp","","crust","","","","crash","","","cosec","","coset","cased","","","","","","","","","carex","","caret","","","","","","","","","","","","","close","","chest","cause","","caste","cease","","cesta","corse","","","carse","","carse","","","","cruse","","crest","","","","","",""},
{"gloam","","datum","flank","","draft","murra","","dorty","doing","","","drily","","drift","dairy","","","lanky","","dicty","drain","","droit","dinar","","dirty","pylon","","doted","dreed","","","vapor","","doter","","","","dried","","","","","","pinky","","","","","","mirky","","","coaly","","leapt","mauve","","","barmy","","derat","dwine","","deity","drive","","","","","","axone","","debit","","","","deair","","","fugal","","canto","gumbo","","drats","korun","","darts","","","doits","dribs","","","","","","viola","","dints","","","","dirks","","dirts","comal","","dates","drees","","","dares","","","","","","dries","","dries","","","","munch","","dites","drees","","","","","","leman","","deets","dregs","","","deers","","","deils","","","dribs","","","","","","defis","","diets","","","","","","","dusky","","dusty","","","","dorsa","","durst","daisy","","","","","","","","","disci","","didst","","","","","","","dosed","","","","","","doser","","","","","","dried","","","","","","","","","","","","","","","douse","","doest","druse","","drest","","","","deism","","deist","","","","","","","disme","","","","","","","",""},
{"ender","","eaved","elder","","eland","expel","","early","eying","","erica","elide","","","edile","","","equid","","","elfin","","elain","ervil","","","erose","","erase","","","","","","","","","","","","","","","","","","","","","","","","","corns","","eases","elves","","elans","enols","","earls","emirs","","","","","","evils","","","eidos","","","","","","","","","erect","","expat","elect","","","exult","","eclat","edict","","","elint","","","","","","eight","","","","","","","","","egest","","","","","","","","","exist","","","","","","exist","","","","","","","","","","","","escot","","","","","","","","","","","","elint","","","","","","","","","","","","","","","ether","","eaten","elute","","elate","ethyl","","","evite","","","elite","","","","","","ethic","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","estop","","easts","","","","","","","exits","","","","","","","","","etuis","","","","","","","",""},
{"guano","","float","manly","","filth","fugio","","faint","today","","forth","firry","","firth","farci","","","drouk","","front","filar","","","frail","","fritt","madly","","facet","fixed","","filet","flied","","","fared","","","fired","","","","","","freed","","","unbox","","","frier","","","macle","","flyte","field","","","felid","","feint","comae","","forte","","","","feria","","","freak","","fetor","fibre","","","","","","would","","fasts","knoll","","fiats","foils","","flits","dolma","","farts","firms","","","","","","agony","","frats","fiars","","","fairs","","frits","amuck","","fates","vocal","","","flies","","","fores","","","fires","","fires","fores","","","frees","","","vocal","","","fries","","fries","fuels","","fetas","fiefs","","","","","","ferns","","","firms","","","","","","fears","","frets","","","","","","","flash","","fatso","fishy","","","fusil","","foist","","","","","","first","","","","frosh","","frost","","","","frisk","","","fusel","","","","","","","","","","","","fired","","","","","","","","","","","","","","","fesse","","feast","","","","","","feist","","","","","","","","","","fresh","","","","","","frise","",""},
{"prion","","griot","unbid","","gavot","grana","","grant","gully","","","galax","","","gulag","","","glory","","glint","gaily","","gault","drain","","gloat","drink","","greet","dumpy","","gated","","","","gelee","","","galea","","","","","","glued","","gleet","gavel","","","","","","primo","","getup","gauze","","","cramp","","grate","gelid","","","","","","","","","biome","","","gable","","","craze","","","drown","","fiord","drunk","","gaits","brand","","goats","fillo","","gilts","galas","","","","","","blimp","","gluts","gaols","","","glass","","","houri","","","sumps","","gates","","","","gules","","","gales","","gales","gules","","","glees","","","sumps","","gates","","","","greys","","gents","","","","gears","","getas","gelds","","gelts","galas","","","","","","gleys","","","","","","","","","houri","","gusto","gassy","","","gnash","","ghast","","","","","","","","","","","","glost","","","","","","","","","","","","","","","","","","","galea","","","","","","","","","","","","","","","gorse","","geest","","","","","","","","","","","","","","","","","","","","","","","",""},
{"tonic","","holly","unity","","halma","hogan","","holla","hurry","","hurly","harry","","","horah","","horal","humor","","","hairy","","","hoary","","hilar","wonky","","hovel","ditzy","","haled","","","","hired","","","hared","","","","","","poind","","","hazer","","haler","","","","hinge","","helio","hance","","halve","heavy","","","herry","","","","","","herma","","","henry","","","","","","heard","","","knout","","moult","knits","","molly","hoyas","","hulas","hurts","","hurls","kempt","","harls","horas","","","hours","","","hairs","","","hoars","","","pinko","","holes","vomit","","hales","","","","heres","","","hares","","hares","heres","","","","","","vomit","","hales","","","","hests","","molly","haems","","","heats","","heals","mound","","herls","kempt","","harls","","","","heirs","","","","","","hears","","","hussy","","","hadst","","","hosta","","","horst","","","harsh","","","","","","","","","","","","","","","hosed","","hosel","","","","","","","","","","hared","","","","","","","","","","","","","","","hoise","","","hawse","","","","","","horse","","","","","","","","","","","","","","","","",""},
{"imago","","iotas","","","","ixora","","","ileum","","items","","","","","","","issue","","islet","","","irate","icker","","ither","icons","","","irony","","","","","","","","","","","","","","","imine","","","irone","","","","","","ionic","","input","","","","inurn","","intro","","","inept","","","","","","inert","ingle","","inlet","","","","inner","","inter","iliad","","","","","","","","","","","","","","","","","","spiel","","","irked","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","inked","","","","","","","","","idols","","idiot","","","","","","","ideal","","","","","","","","","idles","","","irade","","","idler","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","indow","","","","","","indri","","","","","","","","","","","","indue","","","","","","","",""},
{"muton","","jocko","mungo","","jacky","jurat","","","jolly","","","jalop","","","","","","jowly","","","jacal","","","jural","","","divvy","","joked","japed","","","","","","julep","","","","","","","","","jewel","","","","","","","","","nitre","","jerky","jambe","","","jehad","","","jelly","","","","","","","","","joule","","","","","","","","","motif","","junks","javas","","jacks","jotas","","","jilts","","","","","","","","","jowls","","","jails","","","","","","cubit","","jokes","japes","","jakes","","","","joles","","","","","","joles","","","","","","japes","","jakes","","","","jeers","","jerks","","","","jeans","","","jells","","","","","","","","","","","","","","","","","","joist","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","jesse","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"kilty","","colts","known","","knots","kinky","","konks","khaki","","khats","knack","","knaps","kiang","","khans","patio","","kakis","","","","","","kains","kukri","","","knurl","","knurs","","","","","","","","","knars","","","","kauri","","","","","","","","","krill","","kirks","","","","korun","","kirns","krait","","","knaur","","","","","","karat","","karst","","","","krona","","karns","kedge","","","knife","","","koine","","","","","","knave","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","kyrie","","","","","","kerne","","","","","","knave","","","","","","","","","","","","","","","kelep","","pelts","kneel","","knees","kench","","kenos","","","","","","","","","","kebab","","kales","knead","","","","","kanes","kerry","","kiers","","","","","","","","","","","","knars","","","","","","","","","","","","","kiter","","kerbs","","","","","","kerns","","","","","","","","","","kebar","","","","","","","",""},
{"mingy","","licht","mingy","","lathi","mincy","","loath","lyric","","lirot","choky","","","loral","","","libri","","","labra","","","libra","","lyart","dinky","","lunet","dyked","","latex","lycea","","lutea","lured","","","laree","","","","","","genip","","liter","mucky","","later","","","","yogin","","lithe","lance","","latte","leavy","","leant","","","","large","","","","","","lucre","","litre","","","","learn","","","pinko","","futon","nicad","","lasts","nomad","","lotas","loris","","","larks","","","liras","","","lours","","","lairs","","","liars","","","begun","","lutes","munch","","","","","","lyres","","","lares","","lares","lyres","","","","","","munch","","","","","","denim","","leets","","","","kendo","","","","","","larks","","","","","","leers","","","","","","lears","","","lossy","","lusty","lasso","","","","","","","","","","","","","","","","","","","","","","","","losel","","","lased","","","","","","","","","laree","","","","","","loser","","","laser","","laser","","","","lowse","","","lapse","","","lease","","least","","","","","","","","","","","","","","","","","",""},
{"loury","","ruing","lyric","","ginny","world","","monad","hooty","","muton","matzo","","matin","","","","mouth","","month","magot","","manta","","","","world","","miner","crazy","","maned","","","","loury","","","matey","","","","","","","","","","","","","","","livre","","minke","livre","","mange","medal","","menad","metre","","","matte","","","metal","","","merit","","monte","","","","meaty","","meant","drouk","","drouk","lurid","","manus","moras","","mynas","ditto","","","maths","","","","","","slots","","mints","mauts","","","moats","","","lurid","","mines","brock","","manes","","","","mutes","","","mates","","mates","mutes","","","","","","brock","","manes","","","","below","","menus","","","","meals","","means","meths","","","maths","","","","","","meets","","","","","","meats","","","mousy","","","massy","","mason","miasm","","","","","","","","","","","","misty","","","maist","","","","","","muser","","","maser","","","","","","","","","matey","","","","","","","","","","","","","","","curse","","mesne","marse","","manse","","","mensa","","","","","","","","","","moste","","","","","","","",""},
{"nobly","","","vying","","naric","nidal","","noria","nitty","","nitro","natty","","","notal","","","ninth","","north","","","","","","","mould","","newer","naled","","namer","","","","noted","","niter","","","","","","","nonet","","","","","","","","","niece","","nervy","nance","","nacre","novae","","","netty","","nitre","","","","","","","","","","","","","neath","","","could","","noris","nanas","","narks","nomas","","","","","","","","","","","","nowts","","","","","","","","","odium","","","naves","","nares","","","","nites","","","nates","","nates","nites","","","","","","naves","","nares","","","","geode","","nerds","","","","neaps","","nears","netts","","","","","","","","","nests","","nerts","","","","neats","","","noisy","","","nasal","","","","","","nutsy","","","","","","","","","","","","nasty","","","","","","nosey","","","","","","","","","","","","","","","","","","","","","","","","","","","noise","","nurse","","","","","","","","","","","","","","","","neist","","","","","","","",""},
{"unhip","","octad","orbit","","orang","occur","","ottar","","","","","","","","","","ology","","octal","","","","","","","notch","","oaken","orbed","","","futon","","oared","oiled","","","","","","ogler","","","olden","","","oriel","","","older","","","ovine","","omega","","","orate","outre","","opera","","","","","","","","","","olive","","","","","","","","","omits","","oasts","ornis","","orcas","odors","","okras","","","","","","","","","","","","opals","","","orals","","","","oozes","","oases","","","","ogres","","","ogles","","","orles","","orles","ogles","","","","","","","","","","","","ovens","","","","","","overs","","","","","","","","","","","","oleos","","","","","","","","","odist","","ossia","","","","","","","","","","","","","","","","osmol","","","","","","","","","onset","","","","","","osier","","","","","","","","","","","","ousel","","","","","","","","","obese","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"count","","colin","minty","","pally","piano","","clift","porny","","","hydro","","parol","","","","moony","","prill","payor","","","prank","","pilar","dinky","","piled","tyned","","palet","","","pilea","purer","","","pareu","","","perea","","","drink","","puler","typic","","paler","","","","tonic","","plebe","paeon","","padle","peace","","gland","perdy","","peril","parge","","parle","","","","pride","","prole","padre","","","peart","","pearl","mount","","dully","think","","mills","cumin","","plays","joint","","purls","kited","","","","","","smogs","","","pairs","","","meaty","","","bunko","","helio","ungot","","pales","","","","pores","","","pares","","pares","pores","","","prees","","","ungot","","pales","","","","steno","","plews","","","","peats","","peals","perms","","","kited","","","","","","gripy","","","","","","pears","","","potsy","","plush","pasty","","palsy","pshaw","","plasm","pursy","","","","","","","","","prosy","","","","","","","","","posed","","","paseo","","","","","","","","","pareu","","","","","","poser","","","","","","","","","posse","","pulse","passe","","","pease","","","perse","","","parse","","parle","","","","prese","","","","","","prase","",""},
{"quaky","","quota","","","","quark","","quart","quipu","","quilt","","","","quirk","","quirt","quail","","quoit","","","","","","","queen","","","","","","queer","","","","","quiet","","","","","","","","","","","","","","","","quale","","quate","","","","query","","","","","quite","","","","quire","","","","","","","","","","","","gaudy","","","","","","","","","quips","","quits","","","","","","","quais","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","queys","","","","","","","","","","","","","","","","","","","","","","","","","","","quash","","","","","","qursh","","","","","","","","","","","","quasi","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","quest","","","","","","","","","","","","","","","","","","","","","","","",""},
{"muton","","hotly","ritzy","","riata","rutin","","rawin","ruddy","","radar","ridgy","","","","","radii","rowdy","","randy","rigid","","","","","rapid","velum","","latke","paver","","","","","","ruder","","","rider","","","","","","vowel","","tacky","clump","","","","","","couth","","tench","rifle","","","gonif","","ramie","deoxy","","redan","ridge","","","redid","","redia","reedy","","readd","","","","rebid","","","knout","","manta","clonk","","rials","roils","","rains","rudds","","","","","","","","","roods","","rands","rinds","","","","","raids","bosun","","sacks","mulct","","","","","","redes","","","rides","","rides","redes","","","","","","mulct","","","","","","kelep","","pearl","riels","","","reifs","","","redds","","","","","","","","","reeds","","reads","","","","","","","roust","","raspy","rishi","","","rosin","","","","","","","","","","","","","","","","","","","","","reset","","raser","risen","","","","","","","","","rider","","","","","","rosed","","rased","","","","","","","reuse","","resaw","rinse","","","resin","","raise","","","","","","","","","","resod","","","","","","resid","",""},
{"conus","","yourn","bungs","","slops","kills","","spill","knows","","corns","wingy","","slaps","chill","","spall","maria","","curdy","","","","fillo","","salps","chows","","spits","slots","","","silts","","","wicks","","spats","slats","","","","","","softa","","sputa","","","","salts","","","korun","","strop","","","slipt","still","","spilt","grins","","staph","slant","","","stall","","","ottar","","strap","","","","sault","","splat","rhino","","cornu","slime","","slipe","selle","","spile","drown","","dreck","slake","","","swale","","spale","sarge","","","","","","sable","","","hilum","","spite","","","","","","","skate","","spate","slate","","slate","skate","","spate","saute","","","","","","","","","krone","","stupe","","","","style","","","grind","","","slake","","","stale","","spale","setae","","","","","","","","","heder","","spies","sleds","","sleep","hills","","spiel","seams","","spaed","","","","seals","","","warns","","spean","","","","selah","","sepal","setts","","septs","","","","","","","seats","","","slats","","","","","","","","septa","","","","","","","wires","","steps","sleet","","slept","smelt","","spelt","","","","","","","","","","mawed","","","","","","steal","",""},
{"mingy","","typic","blink","","","colin","","topaz","throb","","thrip","tarot","","","thraw","","","hullo","","tromp","tatar","","tapir","liang","","tramp","downy","","topee","taxed","","taped","tinea","","","tyred","","","tared","","","","","","wound","","toper","womby","","taper","","","","whine","","tempo","table","","taupe","hence","","tepal","terne","","","targe","","","terra","","","koine","","trope","","","","trade","","","gonif","","typos","clunk","","tapis","tolas","","","uncoy","","turps","tarts","","tarps","toras","","","grimy","","trips","","","","trass","","traps","linum","","topes","climb","","tapes","twaes","","","tyres","","","tares","","tares","tyres","","","trues","","","climb","","tapes","","","","tents","","temps","taels","","","teats","","tepas","terms","","","tarts","","tarps","","","","tryst","","","","","","tears","","","tushy","","tipsy","tansy","","","toast","","","torsk","","","tarsi","","","","","","trust","","","","","","trash","","","","","","","","","","","","","","","tared","","","","","","","","","","","","","","","those","","","tasse","","","testa","","","terse","","","","","","","","","","","","","","","","",""},
{"umped","","upset","urged","","","plebs","","utter","usage","","","urare","","urate","","","","usual","","","ureal","","","umbra","","ultra","","","uplit","","","","","","","","","","","","","","","","","","","","","","","","","","","utile","","","","","","uteri","","","","urari","","","","","","","","","urial","","","","","","unpen","","","","","","","","","","","","","","","","","","unban","","","urban","","","","","","unpin","","","","","","","","","","","","","","","","","","","","","","","","","","","union","","","","","","","","","","","","","","","","","","","","","","","","","","","waxed","","enols","","","","under","","","ulans","","unapt","","","","unarm","","","unsay","","unhat","","","","ulnar","","","unbid","","unlit","","","","unrig","","","","","","","","","","","","uncia","","","","","","","","","unify","","unity","urine","","","","","","","","","","","","","","","","","","","","","","",""},
{"unrig","","virtu","varna","","vatic","vinca","","vitta","villi","","volti","valid","","","volva","","volta","vigil","","","vagal","","vault","viral","","vital","minor","","voted","vaned","","","","","","viler","","","","","valet","","","","vowel","","","","","","","","","genie","","vetch","vague","","","veena","","vitae","velum","","veldt","value","","","velar","","","voile","","","","","","vealy","","","vinos","","","varus","","vasts","vivas","","","vills","","volts","","","","","","","viols","","","vails","","","vials","","","ricin","","votes","vanes","","","","","","voles","","","vales","","vales","voles","","","","","","vanes","","","","","","viers","","vests","","","","","","","velds","","","","","","","","","veils","","","","","","veals","","","visor","","visit","","","vasty","","","vista","","","","","","","","","","","","","vasal","","","","","","vised","","","","","","","","","","","","","","valet","","","","","","","","","","","","","verse","","verst","","","","","","vesta","","","","valse","","valse","","","","","","","","","","","",""},
{"poind","","witty","hulky","","watch","woman","","witan","wordy","","worth","","","warty","wirra","","","ghoul","","whort","","","","wrang","","wrapt","vined","","wited","linky","","","","","","wired","","","wared","","","","","","bipod","","","godly","","water","","","","diene","","withe","wacke","","","whale","","wheat","","","","","","","","","","where","","write","","","","weary","","","poind","","wists","pulik","","nitty","whaps","","whats","worms","","worts","punky","","warts","","","","whirs","","writs","wairs","","","wraps","","","vinyl","","wites","klong","","","","","","wires","","","wares","","wares","wires","","","wries","","","klong","","","","","","needy","","seels","","","","weals","","","","","","upend","","warts","","","","weirs","","","","","","wears","","","whisk","","whist","washy","","waist","wisha","","","","","worst","","","","","","","","","wrist","","","","","","","wised","","","","","","","","","","","","wared","","","","","","wiser","","","","","","","","","welsh","","weest","","","waste","","","","worse","","","","","","","","","","","wrest","","","","","",""},
{"","","","","xerox","xerox","xylem","xylem","","","","","xenon","xenon","","","","","","","","","","","","","","","","","","","","","","","","","","xenia","xenia","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","xeric","xeric","","","","","","","","xenic","xenic","xenic","","","","","","","xeric","xeric","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","xenia","xenia","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"yucch","","","yacht","","yauld","yucca","","yulan","","","","","","","yurta","","","yourn","","","yaird","","","","","","yoked","","yodel","yamen","","","","","","","","","yarer","","","","","","","","","yager","","","","","","yince","","yield","","","","yenta","","","","","","","","","yerba","","","","","","","","","yearn","","","yonis","","yills","yanks","","yawls","yogas","","","yirrs","","","yards","","","","","","yours","","","","","","","","","yikes","","yules","","","","","","","yores","","","","","","yores","","","","","","","","","","","","yetis","","yells","","","","yeans","","","yerks","","","yards","","","","","","","","","","","","years","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","yarer","","","","","","","","","","","","","","","youse","","","","","","yeast","","","","","","","","","","","","","","","","","","","",""},
{"zappy","","zloty","zebra","","","zoeae","","zoeal","zanza","","zonal","","","","zoned","","","","","","","","","zazen","","","zizit","","","","","","zowie","","","","","","","","","","","","zayin","","","","","","","","","ziram","","zilch","","","","zaire","","","zingy","","","","","","","","","","","","","","","","","","zooms","","","tarok","","zeals","zoeas","","","zonks","","","","","","zones","","","zoons","","","","","","","","","zitis","","","","","","","","","","","","","","","","","","","","","","","","","","","","","zills","","","","","","","zincs","","","","","","","","","","","","","","","","","","","","","zesty","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""},
};

int second_guess[NUMC][NUM_S_G];

// states of |c|
const char UNKNOWN = 0;
// the bits 1, 2, 4, 8, 16 show the silver (wrong) positions
const char RED = 31;  // no occurences other than gold
const char UNSATISFIED_SILVER = 32;  // has occurences other than gold (real silver)

double lose_penalty = -1e9;

const int MAP_SIZE_THRESHOLD = 200 * 1024 * 1024 / 72;  // 200M

// temp buffers
int visit[NUMC], vn = 0;
int visit_big[NUM_SCRAMBLE], vn_big = 0;

int letter_count[NUMC][WORD_LEN];
int letter_counts[NUMC];
int sum_letter_count;

int init_letter = 0;  // ranging [0, NUMC)
bool is_first_guess = true;

class State {
public:
	char gold[WORD_LEN];  // correct letters
	char remaining_guesses;
	char c[NUMC];
	size_t hash_value;
	State() {
		memset(gold, 0, sizeof(gold));
		remaining_guesses = 0;
		memset(c, UNKNOWN, sizeof(c));
		hash_value = 0;
	}
	void compute_hash() {
		hash_value = remaining_guesses;
		for (int i = 0; i < WORD_LEN; i++)
			hash_value = hash_value * 26 + gold[i];
		for (int i = 0; i < NUMC; i++)
			hash_value = hash_value * 65 + c[i];
	}
	int get_heuristics(int guess, bool is_possible_answer, int num_possible_answers) const {
		vn++;
		int ret = 0;
		if (is_possible_answer) {
			ret += sum_letter_count * (3 + (1 << (5 - remaining_guesses)) + 150.0 / num_possible_answers) / 2;  // possible answer: (3+(1-16)+(0-150))0.5x
		}
		for (int i = 0; i < WORD_LEN; i++) {
			if (scramble[guess][i] != gold[i] && gold[i]) {
				visit[gold[i] - 'a'] = vn;
			}
		}
		for (int i = 0; i < WORD_LEN; i++) {
			// possible gold or new silver: (1.5 + 0.1875)x
			// possible given silver at a different place: 0.75x
			// possible silver: 0.1875x
			if (c[scramble[guess][i] - 'a'] == RED) {
				continue;
			}
			if (i > 0 && gold[i - 1] == 'q' && scramble[guess][i] == 'u') {
				// we know the letter after 'q' must be 'u', so there is no information
				continue;
			}
			if (scramble[guess][i] != gold[i] && !(c[scramble[guess][i] - 'a'] & UNSATISFIED_SILVER) && visit[scramble[guess][i] - 'a'] != vn) {
				ret += letter_counts[scramble[guess][i] - 'a'] * 52;
				ret += sum_letter_count;
				visit[scramble[guess][i] - 'a'] = vn;
			}
			if (i > 0 && scramble[guess][i] != gold[i] && !(c[scramble[guess][i] - 'a'] & (1 << i))) {
				if (c[scramble[guess][i] - 'a'] & UNSATISFIED_SILVER) {
					ret += letter_count[scramble[guess][i] - 'a'][i] * 104;
					ret += sum_letter_count / 2;
				} else {
					ret += letter_count[scramble[guess][i] - 'a'][i] * 26;
					ret += sum_letter_count / 4;
				}
			}
		}
		return ret;
	}
	bool promote_silver_to_gold(int &golden_mask, int letter) {
		// return true iff successfully promoted
		int tmp = golden_mask | (c[letter] & RED);
		tmp = RED ^ tmp;
		assert(tmp);  // at least 1 possible place
		if (tmp == (tmp & (-tmp))) {
			// tmp == lowbit(tmp): only 1 possible place left
			// promote to gold
			for (int k = 0; k < WORD_LEN; k++) {
				if (tmp == (1 << k)) {
					gold[k] = letter + 'a';
					break;
				}
			}
			if (c[letter] & UNSATISFIED_SILVER)
				c[letter] ^= UNSATISFIED_SILVER;
			golden_mask ^= tmp;
			return true;
		}
		return false;
	}
	void apply_guess(int guess, int answer) {
		vn += 2;
		remaining_guesses--;
		int golden_mask = 0;
		for (int i = 0; i < WORD_LEN; i++) {
			if (scramble[guess][i] == scramble[answer][i]) {
				gold[i] = scramble[guess][i];
				if (c[scramble[guess][i] - 'a'] & UNSATISFIED_SILVER)
					c[scramble[guess][i] - 'a'] ^= UNSATISFIED_SILVER;  // clear previous silver
			} else {
				// silver only applies to letters that is not gold
				visit[scramble[answer][i] - 'a'] = vn;
			}
			if (gold[i])
				golden_mask ^= (1 << i);
		}
		for (int i = 0; i < WORD_LEN; i++) {
			if (gold[i] && scramble[guess][i] != gold[i]) {
				// the silver is not unsatisfied here
				visit[gold[i] - 'a']--;
			}
		}
		for (int i = 0; i < WORD_LEN; i++) {
			if (scramble[guess][i] != scramble[answer][i]) {
				// not gold -- check silvers
				if (visit[scramble[guess][i] - 'a'] == vn) {
					c[scramble[guess][i] - 'a'] |= (1 << i) | UNSATISFIED_SILVER;
				} else if (visit[scramble[guess][i] - 'a'] == vn - 1) {
					c[scramble[guess][i] - 'a'] |= (1 << i);
				} else {
					// no occurences other than gold
					c[scramble[guess][i] - 'a'] = RED;
				}
			}
		}
		/* do not do this to make it faster
		while (true) {
			bool has_silver_promoted = false;
			for (int i = 0; i < NUMC; i++) {
				if ((c[i] & UNSATISFIED_SILVER) && promote_silver_to_gold(golden_mask, i)) {
					has_silver_promoted = true;
				}
			}
			if (!has_silver_promoted)
				break;
		}*/
	}
	void apply_guess(int guess, bool *result_gold, bool *silver) {
		vn++;
		remaining_guesses--;
		int golden_mask = 0;
		for (int i = 0; i < WORD_LEN; i++) {
			if (result_gold[i]) {
				gold[i] = scramble[guess][i];
				if (c[scramble[guess][i] - 'a'] & UNSATISFIED_SILVER)
					c[scramble[guess][i] - 'a'] ^= UNSATISFIED_SILVER;  // clear previous silver
			}
			if (gold[i])
				golden_mask ^= (1 << i);
		}
		for (int i = 0; i < WORD_LEN; i++) {
			if (gold[i] && scramble[guess][i] != gold[i]) {
				// the silver is not unsatisfiable here
				visit[gold[i] - 'a'] = vn;
			}
		}
		for (int i = 0; i < WORD_LEN; i++) {
			if (silver[i]) {
				if (visit[scramble[guess][i] - 'a'] != vn) {
					c[scramble[guess][i] - 'a'] |= (1 << i) | UNSATISFIED_SILVER;
				} else {
					c[scramble[guess][i] - 'a'] |= (1 << i);
				}
			} else if (!result_gold[i]) {
				// red
				// no occurences other than gold
				c[scramble[guess][i] - 'a'] = RED;
			}
		}
		while (true) {
			bool has_silver_promoted = false;
			for (int i = 0; i < NUMC; i++) {
				if ((c[i] & UNSATISFIED_SILVER) && promote_silver_to_gold(golden_mask, i)) {
					has_silver_promoted = true;
				}
			}
			if (!has_silver_promoted)
				break;
		}
	}
	bool possible_answer(int answer) const {
		vn++;
		// check gold, red or silver
		for (int i = 0; i < WORD_LEN; i++) {
			if (gold[i]) {
				if (gold[i] != scramble[answer][i]) {
					return false;
				}
			} else {
				if (c[scramble[answer][i] - 'a'] & (1 << i)) {
					return false;
				}
				// can satisfy silver here
				visit[scramble[answer][i] - 'a'] = vn;
			}
		}
		// check unsatisfied silver
		for (int i = 0; i < NUMC; i++) {
			if ((c[i] & UNSATISFIED_SILVER) && visit[i] != vn) {
				return false;
			}
		}
		return true;
	}
	void print() const {
		printf("%d ", (int) remaining_guesses);
		for (int i = 0; i < WORD_LEN; i++)
			printf("%c", gold[i] ? gold[i] : '*');
		bool has_red = false;
		for (int i = 0; i < NUMC; i++) {
			if (c[i] && !(c[i] & UNSATISFIED_SILVER)) {
				if (!has_red) {
					printf(", no ");
					has_red = true;
				}
				printf("%c", i + 'a');
				if (c[i] != RED) {
					for (int j = 0; j < WORD_LEN; j++) {
						if (c[i] & (1 << j))
							printf("%d", j);
					}
				}
			}
		}
		bool has_silver = false;
		for (int i = 0; i < NUMC; i++)
			if (c[i] & UNSATISFIED_SILVER) {
				if (!has_silver) {
					printf(", silver ");
					has_silver = true;
				}
				printf("%c", i + 'a');
				for (int j = 0; j < WORD_LEN; j++) {
					if (c[i] & (1 << j))
						printf("%d", j + 1);
				}
			}
	}
	bool operator==(const State &other) const {
		if (remaining_guesses != other.remaining_guesses)
			return false;
		for (int i = 0; i < WORD_LEN; i++)
			if (gold[i] != other.gold[i])
				return false;
		for (int i = 0; i < NUMC; i++)
			if (c[i] != other.c[i])
				return false;
		return true;
	}
};
class StateHash {
public:
	size_t operator()(const State &s) const noexcept {
		return s.hash_value;
	}
};

unordered_map<State, double, StateHash> f;

inline bool hard_case(char initial_letter) {
	return false;
}

void count_letters(const State &s, const vector<int> &possible_answers) {
	memset(letter_count, 0, sizeof(letter_count));
	memset(letter_counts, 0, sizeof(letter_counts));
	sum_letter_count = 0;
	for (auto i : possible_answers) {
		// the first letter is given so we don't count it
		for (int j = 1; j < WORD_LEN; j++) {
			if (!s.gold[j]) {
				letter_count[scramble[i][j] - 'a'][j]++;
				letter_counts[scramble[i][j] - 'a']++;
				sum_letter_count++;
			}
		}
	}
}

void init(int num_scramble, const char *SCRAMBLE_PURE) {
	assert(num_scramble == NUM_SCRAMBLE);
	memset(second_guess, -1, sizeof(second_guess));
	for (int i = 0; i < NUM_SCRAMBLE; i++) {
		memcpy(scramble[i], SCRAMBLE_PURE + i * WORD_LEN, WORD_LEN);
		const string scramble_str = string(scramble[i]);
		for (int j = 0; j < NUMC; j++) {
			if (scramble_str == string(FIRST_GUESS[j])) {
				first_guess[j] = i;
			}
		}
		for (int j = 0; j < NUMC; j++) {
			for (int k = 0; k < NUM_S_G; k++) {
				if (scramble_str == string(SECOND_GUESS[j][k])) {
					second_guess[j][k] = i;
				}
			}
		}
	}
}

int search_max_remaining_guesses;
int search_result;  // the word to guess

const int NUM_SHOW = 5;
pair<double, int> results[NUM_SHOW];
int rsn;

double search(const State &s, const vector<int> &possible_answers) {
	/*printf("search ");
	s.print();
	printf(", %d possible answers\n", (int) possible_answers.size());*/
	if (f.count(s) > 0 && s.remaining_guesses != search_max_remaining_guesses)
		return f[s];
	assert(s.remaining_guesses > 0);
	assert(!possible_answers.empty());
	if (s.remaining_guesses == 1) {
		int ret = possible_answers.size();
		if (s.remaining_guesses == search_max_remaining_guesses) {
			search_result = possible_answers[0];
		}
		if (s.remaining_guesses == search_max_remaining_guesses) {
			rsn = min(NUM_SHOW, (int) possible_answers.size());
			for (int i = 0; i < rsn; i++) {
				results[i] = make_pair(win_points[0] * (1.0 / ret) + lose_penalty * (1 - 1.0 / ret), possible_answers[i]);
			}
		}
		return f[s] = win_points[0] * (1.0 / ret) + lose_penalty * (1 - 1.0 / ret);
	}
	if (possible_answers.size() == 1) {
		if (s.remaining_guesses == search_max_remaining_guesses) {
			search_result = possible_answers[0];
		}
		if (s.remaining_guesses == search_max_remaining_guesses) {
			rsn = 1;
			for (int i = 0; i < rsn; i++) {
				results[i] = make_pair(win_points[s.remaining_guesses - 1], possible_answers[i]);
			}
		}
		return f[s] = win_points[s.remaining_guesses - 1];
	}
	if (possible_answers.size() == 2) {
		if (s.remaining_guesses == search_max_remaining_guesses) {
			search_result = possible_answers[0];
		}
		if (s.remaining_guesses == search_max_remaining_guesses) {
			rsn = 2;
			for (int i = 0; i < rsn; i++) {
				results[i] = make_pair((win_points[s.remaining_guesses - 1] + win_points[s.remaining_guesses - 2]) / 2.0, possible_answers[i]);
			}
		}
		return f[s] = (win_points[s.remaining_guesses - 1] + win_points[s.remaining_guesses - 2]) / 2.0;
	}
	double result = (win_points[0] - 1e-3) * possible_answers.size();  // assume we must win...
	if (hard_case(s.gold[0])) {
		// unless the hard cases
		result = lose_penalty * possible_answers.size();
	}
	int best_guess = -1;
	vector<pair<int, int>> guesses;
	int SEARCH_NUM = 60;
	
	if (s.remaining_guesses == search_max_remaining_guesses) {
		SEARCH_NUM = 200;
		rsn = 0;
	}
	/*if (s.remaining_guesses == search_max_remaining_guesses && possible_answers.size() <= 1000) {
		for (auto i : possible_answers) {
			printf("%s: %d\n", scramble[i], s.get_heuristics(i, true, possible_answers.size()));
		}
	}*/
	count_letters(s, possible_answers);
	if (possible_answers.size() <= s.remaining_guesses) {
		// only guess possible answers
		for (auto i : possible_answers) {
			guesses.emplace_back(s.get_heuristics(i, true, possible_answers.size()), i);
		}
		if (possible_answers.size() <= SEARCH_NUM) {
			sort(guesses.begin(), guesses.end(), greater<pair<int, int>>());
		} else {
			partial_sort(guesses.begin(), guesses.begin() + SEARCH_NUM, guesses.end(), greater<pair<int, int>>());
			guesses.resize(SEARCH_NUM);
		}
	} else {
		guesses.reserve(NUM_SCRAMBLE);
		vn_big++;
		for (auto i : possible_answers) {
			guesses.emplace_back(s.get_heuristics(i, true, possible_answers.size()), i);
			visit_big[i] = vn_big;
		}
		for (int i = 0; i < NUM_SCRAMBLE; i++) {
			if (visit_big[i] != vn_big) {
				guesses.emplace_back(s.get_heuristics(i, false, possible_answers.size()), i);
			}
		}
		/*if (hard_case(s.gold[0]) && s.remaining_guesses >= search_max_remaining_guesses - 1) {
			// worst-case analysis
			for (int ii = 0; ii < NUM_SCRAMBLE; ii++) {
				int i = guesses[ii].second;
				unordered_map<State, int, StateHash> new_answers;
				bool has_correct_one = false;
				for (int j : possible_answers) {
					if (i == j) {
						has_correct_one = true;
						continue;
					}
					// suppose the answer is j
					State new_s = s;
					new_s.apply_guess(i, j);
					new_s.compute_hash();
					new_answers[new_s]++;
				}
				int mx = 0;
				for (auto &it : new_answers) {
					if (it.second > mx)
						mx = it.second;
				}
				guesses[ii].first -= mx * 5200;
			}
		}*/
		partial_sort(guesses.begin(), guesses.begin() + SEARCH_NUM, guesses.end(), greater<pair<int, int>>());
		guesses.resize(SEARCH_NUM);
	}
	for (int ii = 0; ii < (int) guesses.size(); ii++) {
		int i = guesses[ii].second;
		// guess word i
		unordered_map<State, vector<int>, StateHash> new_answers;
		bool has_correct_one = false;
		for (int j : possible_answers) {
			if (i == j) {
				has_correct_one = true;
				continue;
			}
			// suppose the answer is j
			State new_s = s;
			new_s.apply_guess(i, j);
			new_s.compute_hash();
			new_answers[new_s].push_back(j);
		}
		if (new_answers.size() == 1 && s == new_answers.begin()->first) {
			// useless guess, prune it
			continue;
		}
		double current_result = 0;
		int remaining_candidates = possible_answers.size();
		if (has_correct_one) {
			current_result += (double) win_points[s.remaining_guesses - 1];
			remaining_candidates--;
		}
		bool pruned = false;
		for (auto &it : new_answers) {
			double new_result = search(it.first, it.second);
			current_result += new_result * it.second.size();
			remaining_candidates -= it.second.size();
			if (s.remaining_guesses == search_max_remaining_guesses) {
				if (rsn >= NUM_SHOW && current_result + win_points[s.remaining_guesses - 2] * remaining_candidates < results[NUM_SHOW - 1].first) {
					pruned = true;
					break;
				}
			} else {
				if (current_result + win_points[s.remaining_guesses - 2] * remaining_candidates < result) {
					// pruning
					pruned = true;
					break;
				}
			}
		}
		/*if (s.remaining_guesses == search_max_remaining_guesses) {
			printf("searched %d(%d) %s %f %.2f\n", ii, guesses[ii].first, scramble[i], pruned ? lose_penalty + current_result / possible_answers.size() : current_result / possible_answers.size(), clock() / 1000.0);
			fflush(stdout);
		}*/
		if (pruned) {
			continue;
		}
		assert(remaining_candidates == 0);
		if (current_result > result) {
			best_guess = i;
			result = current_result;
		}
		if (s.remaining_guesses == search_max_remaining_guesses) {
			if (rsn < NUM_SHOW) {
				results[rsn] = make_pair(current_result / possible_answers.size(), i);
				for (int j = rsn - 1; j >= 0; j--) {
					if (results[j].first < results[j + 1].first) {
						swap(results[j], results[j + 1]);
					}
				}
				rsn++;
			} else {
				for (int j = 0; j < NUM_SHOW; j++) {
					if (current_result / possible_answers.size() > results[j].first) {
						for (int k = NUM_SHOW - 1; k > j; k--) {
							results[k] = results[k - 1];
						}
						results[j] = make_pair(current_result / possible_answers.size(), i);
					}
				}
			}
		} else {
			if (result >= (win_points[s.remaining_guesses - 1] + (possible_answers.size() - 1) * win_points[s.remaining_guesses - 2])) {
				// max possible result
				break;
			}
		}
	}
	result /= possible_answers.size();
	if (s.remaining_guesses == search_max_remaining_guesses) {
		/*if (!hard_case(s.gold[0])) {
			assert(best_guess != -1);
		}
		if (best_guess == -1) {
			// fall back
			best_guess = possible_answers[0];
		}
		search_result = best_guess;*/
		assert(rsn > 0);
		search_result = results[0].second;
	}
	if (result < win_points[0] && !hard_case(s.gold[0]))
		result = lose_penalty;  // assume we must win
	return f[s] = result;
}
State current_state;
vector<int> possible_answers;
int previous_guess;
double total_answer = 0;
void normalize_result(int word_id, bool *gold, bool *silver) {
	// The game gives more information than we need in the algorithm.
	// Propagate silvers.
	for (int i = 0; i < WORD_LEN; i++) {
		for (int j = 0; j < WORD_LEN; j++) {
			if (i != j && scramble[word_id][i] == scramble[word_id][j] && (silver[i] || silver[j])) {
				if (!gold[i]) {
					silver[i] = true;
				}
				if (!gold[j]) {
					silver[j] = true;
				}
			}
		}
	}
}
const char *guess(int word_guessed, int remaining_guesses, char initial_letter, bool *gold, bool *silver, char *&known_letters) {
	if (remaining_guesses == MAX_GUESS) {
		is_first_guess = true;
		if (f.size() > MAP_SIZE_THRESHOLD)
			f.clear();
		current_state = State();
		current_state.gold[0] = initial_letter;
		current_state.remaining_guesses = MAX_GUESS;
		current_state.compute_hash();
		known_letters = current_state.gold;
		possible_answers.clear();
		for (int i = 0; i < NUM_SCRAMBLE; i++) {
			if (scramble[i][0] == initial_letter) {
				possible_answers.push_back(i);
			}
		}
		search_result = first_guess[initial_letter - 'a'];
		return scramble[search_result];
	} else {
		is_first_guess = false;
		if (word_guessed >= 0 && word_guessed < NUM_SCRAMBLE) {
			search_result = word_guessed;
		}
		normalize_result(search_result, gold, silver);
		State backup_state = current_state;
		current_state.apply_guess(search_result, gold, silver);
		vector<int> new_possible_answers;
		new_possible_answers.reserve(possible_answers.size());
		for (auto i : possible_answers) {
			if (current_state.possible_answer(i)) {
				new_possible_answers.emplace_back(i);
			}
		}
		if (debug_mode) {
			printf("%d possible answer%s", (int) possible_answers.size(), possible_answers.size() == 1 ? "" : "s");
			for (auto i : possible_answers) {
				printf(", %s", scramble[i]);
			}
			printf("\n");
		}
		if (new_possible_answers.empty()) {
			current_state = backup_state;  // restore current_state
			known_letters = current_state.gold;
			return "invalid";
		}
		swap(possible_answers, new_possible_answers);
		known_letters = current_state.gold;
	}
	if (remaining_guesses == MAX_GUESS - 1) {
		// hard second guess, lookup table
		int index = 0;
		for (int i = WORD_LEN - 1; i >= 0; i--) {
			index *= 3;
			if (gold[i])
				index++;
			else if (silver[i])
				index += 2;
		}
		search_result = second_guess[initial_letter - 'a'][index];
		return scramble[search_result];
	}
	count_letters(current_state, possible_answers);
	
	search_max_remaining_guesses = current_state.remaining_guesses;
	search_result = -1;
	//current_state.print();
	double result_val = search(current_state, possible_answers);
	//printf(" %f %d possible answers\n", result_val, (int) possible_answers.size());
	assert(search_result != -1);
	/*if (remaining_guesses == MAX_GUESS - 1) {
		total_answer += result_val * possible_answers.size();
		printf("%f\n", total_answer);
	}*/
	/*printf("Best %d choice%s:\n", min(NUM_SHOW, rsn), (min(NUM_SHOW, rsn) == 1 ? "" : "s"));
	for (int i = 0; i < NUM_SHOW && i < rsn; i++) {
		printf("%s %.2f\n", scramble[results[i].second], results[i].first);
	}*/
	return scramble[search_result];
}
