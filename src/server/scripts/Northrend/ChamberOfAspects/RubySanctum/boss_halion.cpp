/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "MapManager.h"
#include "ruby_sanctum.h"

enum Texts
{
    SAY_INTRO                        = 0, // Meddlesome insects! You are too late. The Ruby Sanctum is lost!
    SAY_AGGRO                        = 1, // Your world teeters on the brink of annihilation. You will ALL bear witness to the coming of a new age of DESTRUCTION!
    SAY_METEOR_STRIKE                = 2, // The heavens burn!
    SAY_PHASE_TWO                    = 3, // You will find only suffering within the realm of twilight! Enter if you dare! (17507)
    SAY_DEATH                        = 4, // Relish this victory, mortals, for it will be your last! This world will burn with the master's return! (17503)
    // Beware the shadow! (17506)
    // I am the light and the darkness! Cower, mortals, before the herald of Deathwing!
    // Not good enough. 17504
    // Another "hero" falls. 17501
};

enum HealthPhaseSwitch
{
	HEALTHSWITCH_PHASE1		=	76, // %
	HEALTHSWITCH_PHASE2		=	51, // %
};

enum Spells
{
    // Halion
    SPELL_CLEAVE                        = 74524,
    SPELL_METEOR_STRIKE                 = 74637,

    SPELL_COMBUSTION                    = 74562,    // Will each tick, apart from the damage, also add a stack to 74567
    SPELL_COMBUSTION_STACK              = 74567,    // If 74562 or 74567 is removed; this will trigger an explosion (74607) based on stackamount.
    SPELL_COMBUSTION_SCALE_AURA         = 70507,    // Aura created in spell_dbc since missing in client dbc. Value based on 74567 stackamount.

    SPELL_FIERY_COMBUSTION_EXPLOSION    = 74607,
    SPELL_FIERY_COMBUSTION_SUMMON       = 74610,
    SPELL_COMBUSTION_DAMAGE_AURA        = 74629,

    SPELL_CONSUMTION                    = 74792,
    SPELL_CONSUMTION_STACK              = 74795,
    SPELL_SOUL_CONSUMPTION_EXPLOSION    = 74799,
    SPELL_SOUL_CONSUMPTION_SUMMON       = 74800,
    SPELL_CONSUMPTION_DAMAGE_AURA       = 74803,

    // Living Inferno
    SPELL_BLAZING_AURA                  = 75885,
    // Halion Controller
    SPELL_COSMETIC_FIRE_PILLAR          = 76006,
    SPELL_FIERY_EXPLOSION               = 76010,
    // Meteor Strike
    SPELL_METEOR_STRIKE_COUNTDOWN       = 74641,
    SPELL_METEOR_STRIKE_AOE_DAMAGE      = 74648,
    SPELL_METEOR_STRIKE_FIRE_AURA_1     = 74713,
    SPELL_METEOR_STRIKE_FIRE_AURA_2     = 74718,
    SPELL_BIRTH_NO_VISUAL               = 40031,

    SPELL_TWILIGHT_PRECISION            = 78243, // Increases Halion's chance to hit by 5% and decreases all players' chance to dodge by 20%
	SPELL_BERSERK                       = 26662, // Increases the caster's attack and movement speeds by 150% and all damage it deals by 500% for 5 min.  Also grants immunity to Taunt effects.
	SPELL_START_PHASE2                  = 74808, // Phases the caster into the Twilight realm, leaving behind a large rift.
	SPELL_TWILIGHT_ENTER                = 74807, // Phases the caster into the Twilight realm - phase 32
	SPELL_TWILIGHT_ENTER2               = 74812, //
	SPELL_SUMMON_TWILIGHT_PORTAL        = 74809, //

	//NEED SCRIPT
	SPELL_TAIL_LASH                             = 74531, // A sweeping tail strike hits all enemies behind the caster, inflicting 3063 to 3937 damage and stunning them for 2 sec.
	SPELL_TWILIGHT_DIVISION                     = 75063, // Phases the caster, allowing him to exist and act simultaneously in both the material and Twilight realms.
	SPELL_TWILIGHT_CUTTER                       = 68114, // 77844 dont work (( Inflicts 13,875 to 16,125 Shadow damage every second to players touched by the shadow beam
	//CORPOREALITY
	SPELL_CORPOREALITY_EVEN                     = 74826, // Deals & receives normal damage
	SPELL_CORPOREALITY_20I                      = 74827, // Damage dealt increased by 10% & Damage taken increased by 15%
	SPELL_CORPOREALITY_40I                      = 74828, // Damage dealt increased by 30% & Damage taken increased by 50%
	SPELL_CORPOREALITY_60I                      = 74829, // Damage dealt increased by 60% & Damage taken increased by 100%
	SPELL_CORPOREALITY_80I                      = 74830, // Damage dealt increased by 100% & Damage taken increased by 200%
	SPELL_CORPOREALITY_100I                     = 74831, // Damage dealt increased by 200% & Damage taken increased by 400%
	SPELL_CORPOREALITY_20D                      = 74832, // Damage dealt reduced by 10% & Damage taken reduced by 15%
	SPELL_CORPOREALITY_40D                      = 74833, // Damage dealt reduced by 30% & Damage taken reduced by 50%
	SPELL_CORPOREALITY_60D                      = 74834, // Damage dealt reduced by 60% & Damage taken reduced by 100%
	SPELL_CORPOREALITY_80D                      = 74835, // Damage dealt reduced by 100% & Damage taken reduced by 200%
	SPELL_CORPOREALITY_100D                     = 74836, // Damage dealt reduced by 200% & Damage taken reduced by 400%

    //N10
    SPELL_FLAME_BREATH                          = 74525, // Inflicts 17,500 to 22,500 Fire damage to players in front of Halion
    SPELL_DARK_BREATH                           = 74806, // Inflicts 17,500 to 22,500 Shadow damage to players in front of Halion
    SPELL_DUSK_SHROUD                           = 75484, // Inflicts 3,000 Shadow damage every 2 seconds to everyone in the Twilight Realm

    //Consumption
	NPC_CONSUMPTION                             = 40135,
	SPELL_MARK_OF_CONSUMPTION                   = 74795, // Dummy effect only
	SPELL_SOUL_CONSUMPTION                      = 74792, // Inflicts 4,000 Shadow damage every 2 seconds for 30 seconds to a random raider. Every time Soul Consumption does damage, it applies a stackable Mark of Consumption.
	SPELL_CONSUMPTION_EXPLODE                   = 74799,
	SPELL_CONSUMPTION_AURA                      = 74803,
};

enum Events
{
    // Halion
    EVENT_ACTIVATE_FIREWALL     = 1,
    EVENT_CLEAVE                = 2,
    EVENT_FLAME_BREATH          = 3,
    EVENT_METEOR_STRIKE         = 4,
    EVENT_FIERY_COMBUSTION      = 5,
    EVENT_PASSIVE_PHASE2		= 6,
    EVENT_CHECK_TWILIGHT		= 7,
    // Halion Controller
    EVENT_START_INTRO           = 8,
    EVENT_INTRO_PROGRESS_1      = 9,
    EVENT_INTRO_PROGRESS_2      = 10,
    EVENT_INTRO_PROGRESS_3      = 11,
    EVENT_CONTROLLER_SEARCH_PLAYER = 12,
    EVENT_CONTROLLER_COPROREALITY  = 13,
    // Meteor Strike
    EVENT_SPAWN_METEOR_FLAME    = 14,

    // Halion Twilight
    EVENT_TWILIGHT_ENRAGE 		= 15,
    EVENT_TWILIGHT_DUSK			= 16,
    EVENT_TWILIGHT_DARKBREATH	= 17,
    EVENT_TWILIGHT_SOULCONSUM	= 18,
    EVENT_TWILIGHT_TAILLASH		= 19,
    EVENT_TWILIGHT_DIVISION		= 20,
};

enum Actions
{
    ACTION_METEOR_STRIKE_BURN   = 1,
    ACTION_METEOR_STRIKE_AOE    = 2,
    ACTION_SWITCH_PHASE_TWO		= 3,
    ACTION_SWITCH_PHASE_THREE	= 4,
    ACTION_START_CORPOREALITY	= 5,
};

enum Phases
{
    PHASE_ALL       = 0,
    PHASE_ONE       = 1,
    PHASE_TWO       = 2,
    PHASE_THREE     = 3,

    PHASE_ONE_MASK = 1 << PHASE_ONE,
    PHASE_TWO_MASK = 1 << PHASE_TWO,
    PHASE_THREE_MASK = 1 << PHASE_THREE,
};

enum Misc
{
    TYPE_COMBUSTION_SUMMON = 1,
    FR_RADIUS			   = 45,
};

enum MovePoints
{
	POINT_CENTER 			= 1,
};

struct Locations
{
    float x, y, z;
};

static Locations SpawnLoc[]=
{
    {3154.99f, 535.637f, 72.8887f},            // 0 - Halion spawn point (center)
};

Position const HalionSpawnPos   = {3156.67f,  533.8108f, 72.98822f, 3.159046f};

class boss_halion : public CreatureScript
{
    public:
        boss_halion() : CreatureScript("boss_halion") { }

        struct boss_halionAI : public BossAI
        {
            boss_halionAI(Creature* creature) : BossAI(creature, DATA_HALION)
            {

            }

            uint32 GetPhase(const EventMap &em)
            {
                switch (em.GetPhaseMask())
                {
					case PHASE_ONE_MASK: return PHASE_ONE;
					case PHASE_TWO_MASK: return PHASE_TWO;
					case PHASE_THREE_MASK: return PHASE_THREE;
                    default:
                        return 0;
                }
            }

            void Reset()
            {
            	events.Reset();
				events.SetPhase(PHASE_ONE);
				events.ScheduleEvent(EVENT_ACTIVATE_FIREWALL, 10000);
				events.ScheduleEvent(EVENT_CLEAVE, urand(8000, 10000), PHASE_ONE);
				events.ScheduleEvent(EVENT_FLAME_BREATH, urand(10000, 12000), PHASE_ONE);
				events.ScheduleEvent(EVENT_METEOR_STRIKE, urand(20000, 25000), PHASE_ONE);
				events.ScheduleEvent(EVENT_FIERY_COMBUSTION, urand(15000, 18000), PHASE_ONE);
            }

            void EnterEvadeMode()
            {
            	if (instance->GetData(DATA_HALION_EVENT) != FAIL)
            		return;

            	instance->SetBossState(DATA_HALION, FAIL);
            	ScriptedAI::EnterEvadeMode();
            }

            void EnterCombat(Unit* /*who*/)
            {
                _EnterCombat();
                Talk(SAY_AGGRO);
                DoCast(me, SPELL_TWILIGHT_PRECISION);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ADD, me);
                instance->SetBossState(DATA_HALION, IN_PROGRESS);
                instance->SetData(DATA_HALION_EVENT, IN_PROGRESS);
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
            }

            void JustReachedHome()
            {
                _JustReachedHome();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
            }

            Position const* GetMeteorStrikePosition() const
            {
                return &_meteorStrikePos;
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage)
			{
            	if (me->HealthBelowPctDamaged(HEALTHSWITCH_PHASE1, damage) && GetPhase(events) == PHASE_ONE)
					DoAction(ACTION_SWITCH_PHASE_TWO);

			}

            void DoAction(const int32 action)
			{
				switch(action)
				{
					case ACTION_SWITCH_PHASE_TWO:
					{
						events.CancelEventGroup(PHASE_ONE);
						DoScriptText(-1666108,me);
						me->GetMotionMaster()->Clear();
						me->GetMotionMaster()->MovePoint(POINT_CENTER, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z);
						Creature* pControl = me->GetMap()->GetCreature(instance->GetData64(DATA_HALION_CONTROLLER));
						if (!pControl)
							pControl = me->SummonCreature(NPC_HALION_CONTROLLER, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 0, TEMPSUMMON_MANUAL_DESPAWN, 1000);
						else if (!pControl->isAlive())
							pControl->Respawn();
						pControl->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
						me->SetInCombatWith(pControl);
						pControl->SetInCombatWith(me);


						break;
					}
					case ACTION_SWITCH_PHASE_THREE:
					{
						break;
					}
				}
			}

            void MovementInform(uint32 type, uint32 id)
            {
            	if (type != POINT_MOTION_TYPE)
            		return;

            	switch (id)
            	{
            		case POINT_CENTER:
            		{
            			DoCast(SPELL_START_PHASE2);
            			events.SetPhase(PHASE_TWO);
            			events.ScheduleEvent(EVENT_PASSIVE_PHASE2, 2500, PHASE_TWO);
            			break;
            		}
            	}
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                	switch (GetPhase(events))
					{
						case PHASE_ONE:
						{
							switch (eventId)
							{
								case EVENT_ACTIVATE_FIREWALL:
									// Firewall is activated 10 seconds after starting encounter, DOOR_TYPE_ROOM is only instant.
									if (GameObject* firewall = ObjectAccessor::GetGameObject(*me, instance->GetData64(DATA_FLAME_RING)))
										instance->HandleGameObject(instance->GetData64(DATA_FLAME_RING), false, firewall);
									break;
								case EVENT_FLAME_BREATH:
									DoCast(me, SPELL_FLAME_BREATH);
									events.ScheduleEvent(EVENT_FLAME_BREATH, 25000, PHASE_ONE);
									break;
								case EVENT_CLEAVE:
									DoCastVictim(SPELL_CLEAVE);
									events.ScheduleEvent(EVENT_CLEAVE, urand(8000, 20000), PHASE_ONE);
									break;
								case EVENT_METEOR_STRIKE:
								{
									if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
									{
										target->GetPosition(&_meteorStrikePos);
										me->CastSpell(_meteorStrikePos.GetPositionX(), _meteorStrikePos.GetPositionY(), _meteorStrikePos.GetPositionZ(), SPELL_METEOR_STRIKE, true, NULL, NULL, me->GetGUID());
										Talk(SAY_METEOR_STRIKE);
									}
									events.ScheduleEvent(EVENT_METEOR_STRIKE, 40000, PHASE_ONE);
									break;
								}
								case EVENT_FIERY_COMBUSTION:
								{
									Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true);
									if (!target)
										target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true);
									if (target)
										DoCast(target, SPELL_COMBUSTION);
									events.ScheduleEvent(EVENT_FIERY_COMBUSTION, 30000, PHASE_ONE);
									break;
								}
								default:
									break;
							}
							break;
						}
						case PHASE_TWO:
							switch (eventId)
							{
								case EVENT_PASSIVE_PHASE2:
								{
									DoCast(me, SPELL_SUMMON_TWILIGHT_PORTAL);
									if (GameObject* pGoPortal = instance->instance->GetGameObject(instance->GetData64(GO_HALION_PORTAL_1)))
										  pGoPortal->SetPhaseMask(31,true);
									if (GameObject* pGoRing = instance->instance->GetGameObject(instance->GetData64(DATA_FLAME_RING)))
										  pGoRing->SetPhaseMask(65535,true);
									if (Creature* pControl = me->GetMap()->GetCreature(instance->GetData64(DATA_HALION_CONTROLLER)))
									{
										me->SetInCombatWith(pControl);
										pControl->SetInCombatWith(me);
									}
									Creature* pTwilight = me->GetMap()->GetCreature(instance->GetData64(DATA_HALION_TWILIGHT));
									if (!pTwilight)
										pTwilight = me->SummonCreature(NPC_HALION_TWILIGHT, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 0, TEMPSUMMON_MANUAL_DESPAWN, 1000);
									else if (!pTwilight->isAlive())
										pTwilight->Respawn();
									pTwilight->SetCreatorGUID(0);
									me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
									instance->SetData(DATA_HALION_TWILIGHT, IN_PROGRESS);
									events.ScheduleEvent(EVENT_CHECK_TWILIGHT, 3000, PHASE_TWO);
									break;
								}
								case EVENT_CHECK_TWILIGHT:
								{
									if (instance->GetData(DATA_HALION_TWILIGHT) == SPECIAL)
									{
										me->RemoveAurasDueToSpell(SPELL_START_PHASE2);
										if (Creature* pControl = me->GetMap()->GetCreature(instance->GetData64(DATA_HALION_CONTROLLER)))
										{
											me->SetInCombatWith(pControl);
											pControl->SetInCombatWith(me);
										}
										if (Creature* pTwilight = me->GetMap()->GetCreature(instance->GetData64(DATA_HALION_TWILIGHT)))
										{
											me->SetHealth(pTwilight->GetHealth());
										}

					                    DoScriptText(-1666109,me);
										me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
										me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
										me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
										me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
										me->SetReactState(REACT_AGGRESSIVE);
										me->SetInCombatWithZone();
										me->ClearUnitState(UNIT_STAT_FOLLOW);
										events.SetPhase(PHASE_THREE);
										if (Unit* target = me->getVictim())
										{
											AttackStart(target);
											SetCombatMovement(true);
											me->GetMotionMaster()->MoveChase(target);
										}
										events.ScheduleEvent(EVENT_CLEAVE, urand(8000, 10000), PHASE_THREE);
										events.ScheduleEvent(EVENT_FLAME_BREATH, urand(10000, 12000), PHASE_THREE);
										events.ScheduleEvent(EVENT_METEOR_STRIKE, urand(20000, 25000), PHASE_THREE);
										events.ScheduleEvent(EVENT_FIERY_COMBUSTION, urand(15000, 18000), PHASE_THREE);
									}
									else
										events.ScheduleEvent(EVENT_CHECK_TWILIGHT, 2000, PHASE_TWO);
									break;
								}

							}
							break;
						case PHASE_THREE:
							switch (eventId)
							{
								case EVENT_FLAME_BREATH:
									DoCast(me, SPELL_FLAME_BREATH);
									events.ScheduleEvent(EVENT_FLAME_BREATH, 25000, PHASE_THREE);
									break;
								case EVENT_CLEAVE:
									DoCastVictim(SPELL_CLEAVE);
									events.ScheduleEvent(EVENT_CLEAVE, urand(8000, 20000), PHASE_THREE);
									break;
								case EVENT_METEOR_STRIKE:
								{
									if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
									{
										target->GetPosition(&_meteorStrikePos);
										me->CastSpell(_meteorStrikePos.GetPositionX(), _meteorStrikePos.GetPositionY(), _meteorStrikePos.GetPositionZ(), SPELL_METEOR_STRIKE, true, NULL, NULL, me->GetGUID());
										Talk(SAY_METEOR_STRIKE);
									}
									events.ScheduleEvent(EVENT_METEOR_STRIKE, 40000, PHASE_THREE);
									break;
								}
								case EVENT_FIERY_COMBUSTION:
								{
									Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true);
									if (!target)
										target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true);
									if (target)
										DoCast(target, SPELL_COMBUSTION);
									events.ScheduleEvent(EVENT_FIERY_COMBUSTION, 30000, PHASE_THREE);
									break;
								}
							}
							break;
                    }
                }

                DoMeleeAttackIfReady();
            }

        private:
            Position _meteorStrikePos;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetRubySanctumAI<boss_halionAI>(creature);
        }
};

typedef boss_halion::boss_halionAI HalionAI;


/*######
## boss_halion_twilight (Twilight version)
######*/

class boss_halion_twilight : public CreatureScript
{
public:
    boss_halion_twilight() : CreatureScript("boss_halion_twilight") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_halion_twilightAI(pCreature);
    }

    struct boss_halion_twilightAI : public ScriptedAI
    {
        boss_halion_twilightAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;
        EventMap events;
        bool intro;
        /*
        uint8 stage;
        bool intro;
        uint32 m_uiEnrage;
        uint32 m_uiDuskTimer;
        uint32 m_uiDarkBreathTimer;
        uint32 m_uiSoulCunsumTimer;
        uint32 m_uiTailLashTimer;
        */

        void Reset()
        {
            if(!instance)
                return;

            me->SetRespawnDelay(7*DAY);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            intro = false;
            events.Reset();

            events.ScheduleEvent(EVENT_TWILIGHT_ENRAGE, 600*IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_TWILIGHT_DUSK, 2*IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_TWILIGHT_DARKBREATH, urand(12*IN_MILLISECONDS,20*IN_MILLISECONDS));
            events.ScheduleEvent(EVENT_TWILIGHT_SOULCONSUM, urand(30*IN_MILLISECONDS,40*IN_MILLISECONDS));
            events.ScheduleEvent(EVENT_TWILIGHT_TAILLASH, urand(10*IN_MILLISECONDS,20*IN_MILLISECONDS));

            me->SetInCombatWithZone();
            if (Creature* pControl = me->GetMap()->GetCreature(instance->GetData64(DATA_HALION_CONTROLLER)))
            {
                me->SetInCombatWith(pControl);
                pControl->SetInCombatWith(me);
            }

            Creature* pFocus = me->GetMap()->GetCreature(instance->GetData64(NPC_ORB_ROTATION_FOCUS));
            if (!pFocus )
                 pFocus = me->SummonCreature(NPC_ORB_ROTATION_FOCUS, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 0, TEMPSUMMON_MANUAL_DESPAWN, 1000);
            else if (!pFocus->isAlive())
                 pFocus->Respawn();

            if (Creature* pReal = me->GetMap()->GetCreature(instance->GetData64(DATA_HALION)))
                if (pReal->isAlive())
                    me->SetHealth(pReal->GetHealth());
            if (!me->HasAura(SPELL_TWILIGHT_ENTER))
                 DoCast(me, SPELL_TWILIGHT_ENTER);
        }

        uint32 GetPhase(const EventMap &em)
		{
			switch (em.GetPhaseMask())
			{
				case PHASE_ONE_MASK: return PHASE_ONE;
				case PHASE_TWO_MASK: return PHASE_TWO;
				case PHASE_THREE_MASK: return PHASE_THREE;
				default:
					return 0;
			}
		}

        void EnterEvadeMode()
        {

            if (!instance)
            	return;

            if (instance->GetData(DATA_HALION_EVENT) != FAIL)
            	return;

            instance->SetData(DATA_HALION_TWILIGHT, FAIL);

            ScriptedAI::EnterEvadeMode();
        }

        void MoveInLineOfSight(Unit* pWho)
        {
            if (!instance)
            	return;

            if (!pWho || pWho->GetTypeId() != TYPEID_PLAYER)
            	return;

            if ( !intro && pWho->IsWithinDistInMap(me, 20.0f))
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                events.SetPhase(PHASE_TWO);
                intro = true;
                AttackStart(pWho);
                DoCast(me, SPELL_TWILIGHT_PRECISION);
                if (Creature* pReal = me->GetMap()->GetCreature(instance->GetData64(DATA_HALION)))
                    if (pReal->isAlive())
                       me->SetHealth(pReal->GetHealth());
            }

        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        {
        	if (me->HealthBelowPctDamaged(HEALTHSWITCH_PHASE2, damage) && GetPhase(events) == PHASE_TWO)
        		DoAction(ACTION_SWITCH_PHASE_THREE);
        }

        void DoAction (uint32 id)
        {
        	switch (id)
        	{
				case ACTION_SWITCH_PHASE_THREE:
				{
					if (instance->GetData(DATA_HALION_TWILIGHT) == SPECIAL)
						break;

					DoScriptText(-1666109,me);
					DoCast(SPELL_TWILIGHT_DIVISION);
					events.ScheduleEvent(EVENT_TWILIGHT_DIVISION, 2500);
					break;
				}
        	}
        }
        void JustDied(Unit* pKiller)
        {
            if (!instance)
                return;

            DoScriptText(-1666104,me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_ENTER);

            if (GameObject* pGoPortal = me->FindNearestGameObject(GO_HALION_PORTAL_1, 50.0f))
                   pGoPortal->Delete();
            if (GameObject* pGoPortal = me->FindNearestGameObject(GO_HALION_PORTAL_2, 50.0f))
                   pGoPortal->Delete();
            if (GameObject* pGoPortal = me->FindNearestGameObject(GO_HALION_PORTAL_3, 50.0f))
                   pGoPortal->Delete();

            if (Creature* pReal = me->GetMap()->GetCreature(instance->GetData64(DATA_HALION)))
                if (!pReal->isAlive())
                {
                    instance->SetData(DATA_HALION, DONE);
                    pReal->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
                }
        }

        void KilledUnit(Unit* pVictim)
        {
            switch (urand(0,1))
            {
                case 0:
                    DoScriptText(-1631006,me,pVictim);
                    break;
                case 1:
                    DoScriptText(-1631007,me,pVictim);
                    break;
            }
        }

        void EnterCombat(Unit* pWho)
        {
            if (!instance)
                return;
        }

        void UpdateAI(const uint32 diff)
        {

            if (!me->HasAura(SPELL_TWILIGHT_ENTER))
                 DoCast(me, SPELL_TWILIGHT_ENTER);

            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STAT_CASTING))
            	return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
					case EVENT_TWILIGHT_DUSK:
					{
						if (!me->IsNonMeleeSpellCasted(false))
							DoCast(SPELL_DUSK_SHROUD);
						events.ScheduleEvent(EVENT_TWILIGHT_DUSK, 2*IN_MILLISECONDS);
						break;
					}

					case EVENT_TWILIGHT_DARKBREATH:
					{
						DoCast(SPELL_DARK_BREATH);
						events.ScheduleEvent(EVENT_TWILIGHT_DARKBREATH, urand(12*IN_MILLISECONDS,20*IN_MILLISECONDS));
						break;
					}

					case EVENT_TWILIGHT_TAILLASH:
					{
						DoCast(SPELL_TAIL_LASH);
						events.ScheduleEvent(EVENT_TWILIGHT_TAILLASH, urand(10*IN_MILLISECONDS,20*IN_MILLISECONDS));
						break;
					}

					case EVENT_TWILIGHT_SOULCONSUM:
					{
						if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 45.0f, true))
							DoCast(pTarget, SPELL_SOUL_CONSUMPTION);
						else if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 45.0f, true))
							DoCast(pTarget, SPELL_SOUL_CONSUMPTION);

						events.ScheduleEvent(EVENT_TWILIGHT_SOULCONSUM, urand(30*IN_MILLISECONDS,40*IN_MILLISECONDS));
						break;
					}

					case EVENT_TWILIGHT_DIVISION:
					{
						instance->SetData(DATA_HALION_TWILIGHT, SPECIAL);
						if (GameObject* pGoPortal = me->SummonGameObject(GO_HALION_PORTAL_3, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 4.47206f, 0, 0, 0.786772f, -0.617243f, 99999999))
						{
							pGoPortal->SetPhaseMask(32,true);
							pGoPortal->SetRespawnTime(9999999);
							pGoPortal->SetOwnerGUID(NULL);
						}
						break;
					}

				}

				if (eventId == EVENT_TWILIGHT_ENRAGE)
				{
					 DoCast(SPELL_BERSERK);
					 DoScriptText(-1666105,me);
				}
			}
            DoMeleeAttackIfReady();
        }

    };
};

class npc_halion_controller : public CreatureScript
{
    public:
        npc_halion_controller() : CreatureScript("npc_halion_controller") { }

        struct npc_halion_controllerAI : public ScriptedAI
        {
            npc_halion_controllerAI(Creature* creature) : ScriptedAI(creature),
                _instance(creature->GetInstanceScript())
            {
                me->SetPhaseMask(me->GetPhaseMask() | 0x20, true);
            }

            void Reset()
            {
                me->SetReactState(REACT_PASSIVE);
                _events.Reset();
                _events.ScheduleEvent(EVENT_CONTROLLER_SEARCH_PLAYER, 3000);

            }

            void DoAction(int32 const action)
            {
                switch (action)
                {
					case ACTION_INTRO_HALION:
					{
						me->setActive(true);
						_events.ScheduleEvent(EVENT_START_INTRO, 2000);
						_events.ScheduleEvent(EVENT_INTRO_PROGRESS_1, 6000);
						_events.ScheduleEvent(EVENT_INTRO_PROGRESS_2, 10000);
						_events.ScheduleEvent(EVENT_INTRO_PROGRESS_3, 14000);
						break;
					}
					case ACTION_START_CORPOREALITY:
					{
						_events.ScheduleEvent(EVENT_CONTROLLER_COPROREALITY, 1000);
						break;
					}
                }
            }

            bool doSearchPlayerAtRange(float range)
			{
				Map* pMap = me->GetMap();
				if (pMap && pMap->IsDungeon())
				{
					Map::PlayerList const &PlayerList = pMap->GetPlayers();
					if (!PlayerList.isEmpty())
					   for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
					   {
						   if (!i->getSource()->IsInMap(me)) continue;
						   if (i->getSource()->isGameMaster()) continue;
						   if (i->getSource()->isAlive()  && i->getSource()->IsWithinDistInMap(me, range))
							   return true;
					   }
				}
				return false;
			}

            void UpdateAI(uint32 const diff)
            {
                _events.Update(diff);

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_INTRO:
                            DoCast(me, SPELL_COSMETIC_FIRE_PILLAR, true);
                            break;
                        case EVENT_INTRO_PROGRESS_1:
                            for (uint8 i = 2; i < 4; ++i)
                                if (GameObject* tree = ObjectAccessor::GetGameObject(*me, _instance->GetData64(DATA_BURNING_TREE_1 + i)))
                                    _instance->HandleGameObject(_instance->GetData64(DATA_BURNING_TREE_1 + i), true, tree);
                            break;
                        case EVENT_INTRO_PROGRESS_2:
                            for (uint8 i = 0; i < 2; ++i)
                                if (GameObject* tree = ObjectAccessor::GetGameObject(*me, _instance->GetData64(DATA_BURNING_TREE_1 + i)))
                                    _instance->HandleGameObject(_instance->GetData64(DATA_BURNING_TREE_1 + i), true, tree);
                            break;
                        case EVENT_INTRO_PROGRESS_3:
                            DoCast(me, SPELL_FIERY_EXPLOSION);
                            if (Creature* halion = me->GetMap()->GetCreature(_instance->GetData64(DATA_HALION)))
                            {
                            	halion->SetVisible(true);
                            	halion->SetReactState(REACT_AGGRESSIVE);
                                halion->AI()->Talk(SAY_INTRO);
                            }
                            break;
                        case EVENT_CONTROLLER_SEARCH_PLAYER:
                        	if (_instance->GetData(DATA_HALION_EVENT) == IN_PROGRESS)
                        	{
                        		if (!doSearchPlayerAtRange(50.0f))
                        		{
                        			_instance->SetData(DATA_HALION_EVENT, FAIL);
                        			if (Creature* halion = me->GetMap()->GetCreature(_instance->GetData64(DATA_HALION)))
                        				halion->AI()->EnterEvadeMode();
                        			if (Creature* halionT = me->GetMap()->GetCreature(_instance->GetData64(DATA_HALION_TWILIGHT)))
                        				halionT->AI()->EnterEvadeMode();
                        		}

                        	}
                            _events.ScheduleEvent(EVENT_CONTROLLER_SEARCH_PLAYER, 1000);
                        	break;
                        case EVENT_CONTROLLER_COPROREALITY:
                        	break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap _events;
            InstanceScript* _instance;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetRubySanctumAI<npc_halion_controllerAI>(creature);
        }
};

class npc_meteor_strike_initial : public CreatureScript
{
    public:
        npc_meteor_strike_initial() : CreatureScript("npc_meteor_strike_initial") { }

        struct npc_meteor_strike_initialAI : public Scripted_NoMovementAI
        {
            npc_meteor_strike_initialAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
            }

            void DoAction(int32 const action)
            {
                if (action == ACTION_METEOR_STRIKE_AOE)
                {
                    DoCast(me, SPELL_METEOR_STRIKE_AOE_DAMAGE, true);
                    DoCast(me, SPELL_METEOR_STRIKE_FIRE_AURA_1, true);
                    for (std::list<Creature*>::iterator itr = _meteorList.begin(); itr != _meteorList.end(); ++itr)
                        (*itr)->AI()->DoAction(ACTION_METEOR_STRIKE_BURN);
                }
            }

            void IsSummonedBy(Unit* summoner)
            {
                _owner = summoner->ToCreature();
                if (!_owner)
                    return;

                DoCast(me, SPELL_METEOR_STRIKE_COUNTDOWN);
                DoCast(me, SPELL_BIRTH_NO_VISUAL); // Unknown purpose

                if (HalionAI* halionAI = CAST_AI(HalionAI, _owner->AI()))
                {
                    Position const* ownerPos = halionAI->GetMeteorStrikePosition();
                    Position newpos;
                    float angle[4];
                    angle[0] = me->GetAngle(ownerPos);
                    angle[1] = me->GetAngle(ownerPos) - static_cast<float>(M_PI/2);
                    angle[2] = me->GetAngle(ownerPos) - static_cast<float>(-M_PI/2);
                    angle[3] = me->GetAngle(ownerPos) - static_cast<float>(M_PI);

                    _meteorList.clear();
                    for (uint8 i = 0; i < 4; i++)
                    {
                        MapManager::NormalizeOrientation(angle[i]);
                        me->SetOrientation(angle[i]);
                        me->GetNearPosition(newpos, 10.0f, 0.0f); // Exact distance
                        if (Creature* meteor = me->SummonCreature(NPC_METEOR_STRIKE_NORTH + i, newpos, TEMPSUMMON_TIMED_DESPAWN, 30000))
                            _meteorList.push_back(meteor);
                    }
                }
            }

            void UpdateAI(uint32 const /*diff*/) {}
            void EnterEvadeMode() {}

        private:
            Creature* _owner;
            std::list<Creature*> _meteorList;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetRubySanctumAI<npc_meteor_strike_initialAI>(creature);
        }
};

class npc_meteor_strike : public CreatureScript
{
    public:
        npc_meteor_strike() : CreatureScript("npc_meteor_strike") { }

        struct npc_meteor_strikeAI : public Scripted_NoMovementAI
        {
            npc_meteor_strikeAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
                _range = 5.0f;
                _spawnCount = 0;
            }

            void DoAction(int32 const action)
            {
                if (action == ACTION_METEOR_STRIKE_BURN)
                {
                    DoCast(me, SPELL_METEOR_STRIKE_FIRE_AURA_2, true);
                    me->setActive(true);
                    _events.ScheduleEvent(EVENT_SPAWN_METEOR_FLAME, 500);
                }
            }

            void UpdateAI(uint32 const diff)
            {
                if (_spawnCount > 5)
                    return;

                _events.Update(diff);

                if (_events.ExecuteEvent() == EVENT_SPAWN_METEOR_FLAME)
                {
                    Position pos;
                    me->GetNearPosition(pos, _range, 0.0f);

                    if (Creature* flame = me->SummonCreature(NPC_METEOR_STRIKE_FLAME, pos, TEMPSUMMON_TIMED_DESPAWN, 25000))
                    {
                        flame->CastSpell(flame, SPELL_METEOR_STRIKE_FIRE_AURA_2, true);
                        _spawnCount++;
                    }
                    _range += 5.0f;
                    _events.ScheduleEvent(EVENT_SPAWN_METEOR_FLAME, 800);
                }
            }

        private:
            EventMap _events;
            float _range;
            uint8 _spawnCount;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetRubySanctumAI<npc_meteor_strikeAI>(creature);
        }
};

class npc_combustion : public CreatureScript
{
    public:
        npc_combustion() : CreatureScript("npc_combustion") { }

        struct npc_combustionAI : public Scripted_NoMovementAI
        {
            npc_combustionAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
            }

            void SetData(uint32 type, uint32 data)
            {
                if (type == TYPE_COMBUSTION_SUMMON)
                {
                    //if (Unit* owner = me->GetSummoner())
                    int32 damage = 1200 + (data * 1290); // Hardcoded values from guessing. Need some more research.
                    me->CastCustomSpell(SPELL_FIERY_COMBUSTION_EXPLOSION, SPELLVALUE_BASE_POINT0, damage, me, true);

                    // Scaling aura
                    for (uint32 i = 0; i < data; ++i)
                    	DoCast(me, SPELL_COMBUSTION_SCALE_AURA);
                    DoCast(me, SPELL_COMBUSTION_DAMAGE_AURA);
                }
            }

            void UpdateAI(uint32 const /*diff*/) {}
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetRubySanctumAI<npc_combustionAI>(creature);
        }
};

class spell_halion_meteor_strike_marker : public SpellScriptLoader
{
    public:
        spell_halion_meteor_strike_marker() : SpellScriptLoader("spell_halion_meteor_strike_marker") { }

        class spell_halion_meteor_strike_marker_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_halion_meteor_strike_marker_AuraScript);

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
                {
                    if (Creature* creCaster = GetCaster()->ToCreature())
                        creCaster->AI()->DoAction(ACTION_METEOR_STRIKE_AOE);
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_halion_meteor_strike_marker_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_halion_meteor_strike_marker_AuraScript();
        }
};

class spell_halion_combustion : public SpellScriptLoader
{
    public:
        spell_halion_combustion() : SpellScriptLoader("spell_halion_combustion") { }

        class spell_halion_combustion_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_halion_combustion_AuraScript);

            bool Validate(SpellEntry const* /*spell*/)
            {
                if (!sSpellStore.LookupEntry(SPELL_COMBUSTION_STACK))
                    return false;
                return true;
            }

            void HandleExtraEffect(AuraEffect const* /*aurEff*/)
            {
                GetTarget()->CastSpell(GetTarget(), SPELL_COMBUSTION_STACK, true);
            }

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->CastSpell(GetTarget(), SPELL_COMBUSTION_STACK, true);
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                sLog->outError("spell_halion_combustion: OnRemove");
                if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
                {
                	int32 damage = 4200 + (GetTarget()->GetAuraCount(SPELL_COMBUSTION_STACK) * 1290); // Hardcoded values from guessing. Need some more research.
                	GetCaster()->CastCustomSpell(SPELL_FIERY_COMBUSTION_EXPLOSION, SPELLVALUE_BASE_POINT0, damage, GetTarget(), true);
                }
                if (GetTarget()->HasAura(SPELL_COMBUSTION_STACK))
                    GetTarget()->RemoveAurasDueToSpell(SPELL_COMBUSTION_STACK, 0, 0, AURA_REMOVE_BY_ENEMY_SPELL);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_halion_combustion_AuraScript::HandleExtraEffect, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
                AfterEffectApply += AuraEffectApplyFn(spell_halion_combustion_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_halion_combustion_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_halion_combustion_AuraScript();
        }
};

class spell_halion_combustion_stack : public SpellScriptLoader
{
    public:
        spell_halion_combustion_stack() : SpellScriptLoader("spell_halion_combustion_stack") { }

        class spell_halion_combustion_stack_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_halion_combustion_stack_AuraScript);

            bool Validate(SpellEntry const* /*spell*/)
            {
                if (!sSpellStore.LookupEntry(SPELL_FIERY_COMBUSTION_SUMMON))
                    return false;
                if (!sSpellStore.LookupEntry(SPELL_FIERY_COMBUSTION_EXPLOSION))
                    return false;
                return true;
            }

            void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                sLog->outError("spell_halion_combustion_stack: OnRemove");
                GetTarget()->RemoveAurasDueToSpell(SPELL_COMBUSTION);
                GetTarget()->CastCustomSpell(SPELL_FIERY_COMBUSTION_SUMMON, SPELLVALUE_BASE_POINT0, aurEff->GetBase()->GetStackAmount(), GetTarget(), true);
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_halion_combustion_stack_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_halion_combustion_stack_AuraScript();
        }
};

class spell_combustion_consumption_summon : public SpellScriptLoader
{
    public:
        spell_combustion_consumption_summon() : SpellScriptLoader("spell_combustion_consumption_summon") { }

        class spell_combustion_consumption_summon_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_combustion_consumption_summon_SpellScript);

            void HandleSummon(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Unit* caster = GetCaster();
                uint32 entry = uint32(GetSpellInfo()->EffectMiscValue[effIndex]);
                SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(uint32(GetSpellInfo()->EffectMiscValueB[effIndex]));
                uint32 duration = uint32(GetSpellDuration(GetSpellInfo()));

                Position pos;
                caster->GetPosition(&pos);
                if (TempSummon* summon = caster->GetMap()->SummonCreature(entry, pos, properties, duration, caster, GetSpellInfo()->Id))
                {
                    summon->AI()->SetData(TYPE_COMBUSTION_SUMMON, uint32(GetSpellInfo()->EffectBasePoints[effIndex]));
                    //summon->AddAura(SPELL_COMBUSTION_DAMAGE_AURA, summon);
                }
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_combustion_consumption_summon_SpellScript::HandleSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_combustion_consumption_summon_SpellScript();
        }
};

class go_halion_portal_twilight : public GameObjectScript
{
    public:

        go_halion_portal_twilight() : GameObjectScript("go_halion_portal_twilight") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            InstanceScript* pInstance = (InstanceScript*)go->GetInstanceScript();
            if(!pInstance) return false;
            player->CastSpell(player,SPELL_TWILIGHT_ENTER,false);
            return true;
        }
};

class go_halion_portal_real : public GameObjectScript
{
    public:

        go_halion_portal_real() : GameObjectScript("go_halion_portal_real") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            InstanceScript* pInstance = (InstanceScript*)go->GetInstanceScript();
            if(!pInstance) return false;
            player->RemoveAurasDueToSpell(SPELL_TWILIGHT_ENTER);
            return true;
        }
};

/*######
## mob_orb_rotation_focus
######*/
class mob_orb_rotation_focus : public CreatureScript
{
public:
    mob_orb_rotation_focus() : CreatureScript("mob_orb_rotation_focus") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_orb_rotation_focusAI(pCreature);
    }

    struct mob_orb_rotation_focusAI : public ScriptedAI
    {
        mob_orb_rotation_focusAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            pInstance = (InstanceScript*)pCreature->GetInstanceScript();
            Reset();
        }

        InstanceScript* pInstance;

        uint32 m_timer;
        float m_direction, m_nextdirection;
        bool m_warning;

        void Reset()
        {
            me->SetDisplayId(11686);
//        me->SetDisplayId(10045);
            me->SetRespawnDelay(7*DAY);
            me->SetPhaseMask(65535, true);
            SetCombatMovement(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_direction = 0.0f;
            m_nextdirection = 0.0f;
            m_timer = 30000;
            m_warning = false;

            Creature* pPulsar1 = me->GetMap()->GetCreature(pInstance->GetData64(DATA_SHADOW_ORB_N));
            if (!pPulsar1 )
            {
                float x,y;
                me->GetNearPoint2D(x, y, FR_RADIUS, m_direction);
                pPulsar1 = me->SummonCreature(NPC_SHADOW_ORB_N, x, y, me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN, 5000);
            } else if (!pPulsar1->isAlive())
                        pPulsar1->Respawn();

            Creature* pPulsar2 = me->GetMap()->GetCreature(pInstance->GetData64(DATA_SHADOW_ORB_S));
            if (!pPulsar2)
            {
                float x,y;
                me->GetNearPoint2D(x, y, FR_RADIUS, m_direction + M_PI);
                pPulsar2 = me->SummonCreature(NPC_SHADOW_ORB_S, x, y, me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN, 5000);
            } else if (!pPulsar2->isAlive())
                        pPulsar2->Respawn();
        }

        void AttackStart(Unit *who)
        {
            //ignore all attackstart commands
            return;
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!pInstance)
                  me->ForcedDespawn();
            if (pInstance->GetData(DATA_HALION) != IN_PROGRESS)
                  me->ForcedDespawn();

            if (pInstance->GetData(DATA_SHADOW_ORB_S) == DONE && pInstance->GetData(DATA_SHADOW_ORB_N) == DONE)
            {
                m_direction = m_nextdirection;
                m_nextdirection = (m_direction - M_PI/64.0f);
                if (m_nextdirection < 0.0f ) m_nextdirection = m_nextdirection + 2.0f*M_PI;
                pInstance->SetData(DATA_ORB_DIRECTION, (uint32)(m_nextdirection*1000));
                pInstance->SetData(DATA_SHADOW_ORB_N, SPECIAL);
                pInstance->SetData(DATA_SHADOW_ORB_S, SPECIAL);
                //sLog->outDebug("EventMGR: creature %u send direction %u ",me->GetEntry(),pInstance->GetData(DATA_ORB_DIRECTION));
            }

            if (m_timer - 6000 <= uiDiff && !m_warning)
            {
                DoScriptText(-1666110,me);
                m_warning = true;
            }

            if (m_timer <= uiDiff)
            {
                float x,y;
                me->GetNearPoint2D(x, y, FR_RADIUS, m_nextdirection);
                me->SummonCreature(NPC_ORB_CARRIER, x, y, me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN, 5000);
                m_timer = 30000;
                m_warning = false;
            }   else m_timer -= uiDiff;
        }
    };
};


/*######
## mob_halion_orb
######*/
class mob_halion_orb : public CreatureScript
{
public:
    mob_halion_orb() : CreatureScript("mob_halion_orb") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_halion_orbAI(pCreature);
    }

    struct mob_halion_orbAI : public ScriptedAI
    {
        mob_halion_orbAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            pInstance = (InstanceScript*)pCreature->GetInstanceScript();
            Reset();
        }

        InstanceScript* pInstance;

        float m_direction,m_delta;
        uint32 m_flag;
        uint32 m_flag1;
        bool MovementStarted;
        Creature* focus;
        uint32 nextPoint;

        void Reset()
        {
            if (!pInstance) return;
            me->SetRespawnDelay(7*DAY);
           // me->SetDisplayId(11686);
            SetCombatMovement(false);
            me->SetPhaseMask(32, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            if (me->GetEntry() == NPC_SHADOW_ORB_N)
            {
                m_flag = DATA_SHADOW_ORB_N;
                m_delta = 0.0f;
            } else if (me->GetEntry() == NPC_SHADOW_ORB_S)
            {
                m_flag = DATA_SHADOW_ORB_S;
                m_delta = M_PI;
            };
            m_direction = 0.0f;
            nextPoint = 0;
            MovementStarted = false;
            pInstance->SetData(m_flag, DONE);
            //sLog->outDebug("EventMGR: creature %u assume m_flag %u ",me->GetEntry(),m_flag);
        }

        void AttackStart(Unit *who)
        {
            //ignore all attackstart commands
            return;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (!pInstance) return;

            if (type != POINT_MOTION_TYPE || !MovementStarted) return;

            if (id == nextPoint) {
                    me->GetMotionMaster()->MovementExpired();
                    MovementStarted = false;
                    pInstance->SetData(m_flag, DONE);
                    }
        }

        void StartMovement(uint32 id)
        {
            if (!pInstance) return;
            nextPoint = id;
            float x,y;
            pInstance->SetData(m_flag, IN_PROGRESS);
            MovementStarted = true;
            m_direction = ((float)pInstance->GetData(DATA_ORB_DIRECTION)/1000 + m_delta);
            if (m_direction > 2.0f*M_PI) m_direction = m_direction - 2.0f*M_PI;
            if (focus = me->GetMap()->GetCreature(pInstance->GetData64(DATA_ORB_ROTATION_FOCUS)))
                focus->GetNearPoint2D(x, y, FR_RADIUS, m_direction);
                else me->ForcedDespawn();
//        sLog->outDebug("EventMGR: creature %u go to move point %u ",me->GetEntry(),id);
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MovePoint(id, x, y,  me->GetPositionZ());
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!pInstance)
                  me->ForcedDespawn();
            if (pInstance->GetData(DATA_HALION) != IN_PROGRESS)
                  me->ForcedDespawn();

            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 3.0f, true))
                DoCast(pTarget, SPELL_TWILIGHT_CUTTER);
            else if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 3.0f, true))
                DoCast(pTarget, SPELL_TWILIGHT_CUTTER);

            if (!MovementStarted && pInstance->GetData(m_flag) == SPECIAL)
            {
//            sLog->outDebug("EventMGR: creature %u get direction %u ",me->GetEntry(),pInstance->GetData(DATA_ORB_DIRECTION));
                StartMovement(1);
            }

        }
    };
};


/*######
## mob_orb_carrier
######*/
class mob_orb_carrier : public CreatureScript
{
public:
    mob_orb_carrier() : CreatureScript("mob_orb_carrier") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_orb_carrierAI(pCreature);
    }

    struct mob_orb_carrierAI : public ScriptedAI
    {
        mob_orb_carrierAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            pInstance = (InstanceScript*)pCreature->GetInstanceScript();
            Reset();
        }

        InstanceScript* pInstance;

        bool MovementStarted;

        void Reset()
        {
//        me->SetDisplayId(10045);
         //   me->SetDisplayId(11686);
            me->SetRespawnDelay(7*DAY);
            SetCombatMovement(false);
            me->SetPhaseMask(32, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            MovementStarted = false;
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING); //or remove???
            me->SetSpeed(MOVE_RUN, 6.0f, true);
        }

        void AttackStart(Unit *pWho)
        {
            return;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (!pInstance) return;

            if (type != POINT_MOTION_TYPE || !MovementStarted) return;

            if (id == 1) {
                    me->GetMotionMaster()->MovementExpired();
                    MovementStarted = false;
                    me->ForcedDespawn();
                    }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!pInstance || pInstance->GetData(DATA_HALION) != IN_PROGRESS)
                  me->ForcedDespawn();

            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 3.0f, true))
                DoCast(pTarget, SPELL_TWILIGHT_CUTTER);
            else if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 3.0f, true))
                DoCast(pTarget, SPELL_TWILIGHT_CUTTER);

            if (!MovementStarted)
            {
                float x,y;
                float m_direction = ((float)pInstance->GetData(DATA_ORB_DIRECTION)/1000.0f + M_PI - M_PI/32.0f);
                if (m_direction > 2.0f*M_PI) m_direction = m_direction - 2.0f*M_PI;
                if (Creature* focus = me->GetMap()->GetCreature(pInstance->GetData64(DATA_ORB_ROTATION_FOCUS)))
                    focus->GetNearPoint2D(x, y, FR_RADIUS, m_direction);
                else me->ForcedDespawn();
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MovePoint(1, x, y,  me->GetPositionZ());
                MovementStarted = true;
            }

        }

    };
};

void AddSC_boss_halion()
{
    new boss_halion();
    new boss_halion_twilight();
    new npc_halion_controller();
    new npc_meteor_strike_initial();
    new npc_meteor_strike();
    new npc_combustion();
    new spell_halion_meteor_strike_marker();
    new spell_halion_combustion();
    new spell_halion_combustion_stack();
    new spell_combustion_consumption_summon();
    new go_halion_portal_real();
    new go_halion_portal_twilight();

    new mob_orb_rotation_focus();
    new mob_halion_orb();
    new mob_orb_carrier();
}
