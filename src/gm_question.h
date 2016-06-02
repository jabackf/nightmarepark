#ifndef QUESTION_H
#define QUESTION_H

#include "include_all.h"

#define qcount 18

u16 quiz_answers[]={0,0,1,2,2,3,3,1,0,0,2,3,0,2,1,1,2,2};

const char* quiz_questions[]={
	"WHICH IS THE LEAST#POPULATED STATE IN THE#US?", //0 ALASKA
	"WHAT IS THE CAPITAL OF#IRELAND?", //0 DUBLIN
	"WHO DISCOVERED THAT#THERE ARE OTHER#GALAXIES BEYOND OUR#MILKY WAY?", //1 EDWIN HUBBLE
	"WHICH PLANET IN OUR#SOLAR SYSTEM HAS THE#LONGEST DAY?", //2 VENUS
	"HOW MANY BONES ARE#THERE IN A NORMAL ADULT#HUMAN BODY?", //2 206
	"HOW MUCH VISION DO YOU#LOSE IF YOU GO BLIND IN#ONE EYE?", //3 20 PERCENT
	"THE SCIATIC NERVE CAN#BE FOUND IN WHAT BODY#PART?", //3 LEG
	"BEARS ARE NOT...", //1 SOFT HAIRED
	"WHAT IS THE HARDEST#SUBSTANCE IN THE HUMAN#BODY?", //0 TOOTH ENAMEL
	"WHAT IS THE STRONGEST#MUSCLE IN THE HUMAN#BODY?", //0 JAW
	"WHICH PLANET HAS THE#HIGHEST WINDS?", //2 SATURN
	"THE CHARACTER GRAY FOX#ORIGINATES FROM WHAT#VIDEO GAME?", //3 METAL GEAR
	"WHICH OF THE FOLLOWING#IS NOT A MARSUPIAL?", //0 LLAMA
	"THE SCIENTIFIC STUDY OF#INSECTS IS KNOWN AS...", //2 ENTOMOLOGY
	"ELEPHANT TUSKS ARE MADE#OF WHAT MATERIAL?", //1 IVORY
	"WHICH OF THE FOLLOWING#IS A NATURAL SUGAR#FOUND IN MOST FRUITS?", //1 FRUCTOSE
	"HOW MANY KEYS ARE ON A#STANDARD PIANO?", //2 88
	"WHAT WOULD YOU STUDY IF#YOU WERE A SPELEOLOGIST?" //2 CAVES
};
	
	
const char* quiz_a1[]={
	"ALASKA",
	"DUBLIN",
	"COPERNICUS",
	"MARS",
	"234",
	"50 PERCENT",
	"NECK",
	"OMNIVORIOUS",
	"TOOTH ENAMEL",
	"JAW",
	"URANUS",
	"SPLINTER CELL",
	"LLAMA",
	"ETYMOLOGY",
	"CORAL",
	"NECROSE",
	"20",
	"MINERAL DEPOSITS"
};
	
const char* quiz_a2[]={
	"VERMONT",
	"GALWAY",
	"EDWIN HUBBLE",
	"PLUTO",
	"246",
	"10 PERCENT",
	"HEAD",
	"SOFT HAIRED",
	"BONES",
	"UPPER ARM",
	"MERCURY",
	"SYPHON FILTER",
	"KANGAROO",
	"ICHTHYOLOGY",
	"IVORY",
	"FRUCTOSE",
	"54",
	"TREES"
};

const char* quiz_a3[]={
	"WYOMING",
	"SHANNON",
	"ISAAC NEWTON",
	"VENUS",
	"206",
	"35 PERCENT",
	"TORSO",
	"NOCTURNAL",
	"BONE MARROW",
	"THIGH",
	"SATURN",
	"METAL SLUG",
	"WALLABY",
	"ENTOMOLOGY",
	"BONE",
	"BELLICOSE",
	"88",
	"CAVES"
};
	
const char* quiz_a4[]={
	"MONTANA",
	"LIMERICK",
	"GALILEO",
	"EARTH",
	"258",
	"20 PERCENT",
	"LEG",
	"MAMALS",
	"TOE NAILS",
	"HEART",
	"JUPITER",
	"METAL GEAR",
	"OPOSSUM",
	"PALEONTOLOGY",
	"CALCIUM",
	"PANTIOSE",
	"100",
	"MOUNTAINS"
};

void update_question(void)
{
	u16 r, sel;
	r=RAND(qcount);
	DMA_Copy(3,(void*)bg_questionData, (void*)VideoBuffer,19200, DMA_16NOW);
	draw_text(8,3,65,quiz_questions[r]);
	DMA_Copy(3,(void*)bg_questionPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	mosaic_out(-1);
	sel=make_menu(4,110,-1,0,0,4,quiz_a1[r],quiz_a2[r],quiz_a3[r],quiz_a4[r]);
	mosaic_in(-1);
	if (sel==quiz_answers[r])
		resume_gameboard();
	else
		GameMode=mode_gameover;
}	

#endif
