#ifndef PARTICLES_H
#define PARTICLES_H

#define max_particles 126

typedef struct TS_particle
{
	u16 x, y, wait_to, wait_count, spr;
	s16 vsp, hsp;
	bool move, dead;
} S_part;

typedef struct TS_partsys
{
	u16 count, x, y, spr1, spr2, spr_start, max_wait, grav;
	s16 max_hsp, max_vsp, min_hsp, min_vsp;
	bool constant;
} S_partsys;

S_part particles[max_particles];
S_partsys partsys;

u16 particle_death_count=0;

//Arguments- 
//x - X position in which the particles are spawned
//y - Y position in which the particles are spawned
//grav - The amount of gravity applied to particles
//spr_start - The OAM entry number where the first particle is stored
//spr1 - The data for sprite 1. This is the number used with sprite attribute 2.
//spr2 - The data for sprite 2. If you only want one sprite, pass in 0 here.
//pnum - The number of particles. You can have no more then 126 minus the number of sprites already in OAM.
//max_wait - When a particle is spawned, it will become active after its wait period is up. The wait period is a random number under max_wait.
//min_vsp - The minimum verticle speed for the particles. You can pass a negative number if you want.
//max_vsp - The maximum verticle speed for the particles. This number must be larger then min_vsp.
//min_hsp - The minimum horizontal speed.
//max_hsp - The maximum horizontal speed.
//constant - If the particle system is constant, it will loop until you stop calling part_update. If its not constant, it will fire every particle then die.
//When this happens, part_update will return true.

void part_init(u16 x, u16 y, u16 grav, u16 spr_start, u16 spr1, u16 spr2,u16 pnum, u16 max_wait, s16 min_vsp, s16 max_vsp, s16 min_hsp, s16 max_hsp, bool constant) 
{
	particle_death_count=0;
	
	if (pnum>max_particles) pnum=max_particles;
	x=x<<3;
	y=y<<3;
	partsys.x=x;
	partsys.y=y;
	partsys.spr1=spr1;
	partsys.spr2=spr2;
	partsys.count=pnum;
	partsys.constant=constant;
	partsys.max_wait=max_wait;
	partsys.spr_start=spr_start;
	partsys.grav=grav;
	partsys.max_hsp=max_hsp;
	partsys.max_vsp=max_vsp;
	partsys.min_vsp=min_vsp;
	partsys.min_hsp=min_hsp;
	
	for (int i=spr_start; i<spr_start+pnum; i++)
	{
		sprites[i].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | y>>3;
		sprites[i].attribute1 = SIZE_8 | x>>3;
		if (spr2==0)
			particles[i-spr_start].spr=spr1;
		else
		{
			if (RAND(100)<50) particles[i-spr_start].spr=spr1;
			else particles[i-spr_start].spr=spr2;
		}
		sprites[i].attribute2 = particles[i-spr_start].spr;
		particles[i-spr_start].x=x;
		particles[i-spr_start].y=y;
		particles[i-spr_start].wait_count=0;
		particles[i-spr_start].wait_to=RAND(max_wait);
		particles[i-spr_start].move=false;
		particles[i-spr_start].vsp=0;
		particles[i-spr_start].hsp=0;
		particles[i-spr_start].dead=false;
	}
}

bool part_update()
{
	for (int i=0; i<partsys.count; i++)
	{
		if (particles[i].dead==false)
		{
			if (particles[i].move!=true)
			{
				particles[i].wait_count++;
				if (particles[i].wait_count>=particles[i].wait_to)
				{
					particles[i].wait_count=0;
					particles[i].move=true;
					particles[i].vsp=-(RAND(partsys.max_vsp-partsys.min_vsp)+partsys.min_vsp);
					particles[i].hsp=-(RAND(partsys.max_hsp-partsys.min_hsp)+partsys.min_hsp);
					if (partsys.spr2==0)
						particles[i].spr=partsys.spr1;
					else
					{
						if (RAND(100)<50) particles[i].spr=partsys.spr1;
						else particles[i].spr=partsys.spr2;
					}
					sprites[i+partsys.spr_start].attribute2 = particles[i].spr;
				}
			}
			else
			{
				particles[i].y+=particles[i].vsp;
				particles[i].vsp+=partsys.grav;
				particles[i].x+=particles[i].hsp;
				if (particles[i].y<3 || particles[i].y>1280 || particles[i].x<3 || particles[i].x>1920)
				{
					if (partsys.constant==true)
					{
						particles[i].x=partsys.x;
						particles[i].y=partsys.y;
						particles[i].vsp=0;
						particles[i].hsp=0;
						particles[i].move=false;
						particles[i].wait_to=RAND(partsys.max_wait);
					}
					else	
					{
						particles[i].dead=true;
						particles[i].x=1926;
						particles[i].y=6;
						particle_death_count++;
						if (particle_death_count>=partsys.count) 
						{
							sprites[i+partsys.spr_start].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | particles[i].y>>3;
							sprites[i+partsys.spr_start].attribute1 = SIZE_8 | particles[i].x>>3;
							return true;
						}
					}
				}
				sprites[i+partsys.spr_start].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | particles[i].y>>3;
				sprites[i+partsys.spr_start].attribute1 = SIZE_8 | particles[i].x>>3;
			}
		}
	}
	return false;
}

void part_kill()
{
	particle_death_count=0;
	for (int i=0; i<partsys.count; i++)
	{
		particles[i].x=1926;
		particles[i].y=6;
		particles[i].dead=true;
		particles[i].move=false;
		sprites[i+partsys.spr_start].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | particles[i].y>>3;
		sprites[i+partsys.spr_start].attribute1 = SIZE_8 | particles[i].x>>3;
		CopyOAM();
	}
}

#endif
