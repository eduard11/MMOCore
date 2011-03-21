-- Customize Service
DELETE FROM `creature_template` WHERE (`entry`=993369);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES 
(993369, 0, 0, 0, 0, 0, 26789, 0, 0, 0, 'MMOwning All-in-One', '', '', 0, 80, 80, 0, 35, 35, 1, 0.75, 2, 1755, 1755, 0, 1504, 1000, 1500, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'pryds_allinone');
-- Item Requester
DELETE FROM `creature_template` WHERE (`entry`=993370);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES 
(993370, 0, 0, 0, 0, 0, 26789, 0, 0, 0, 'MMOwning Weihnachtsmann', 'W�nsch dir ein Item', '', 0, 80, 80, 0, 35, 35, 1, 0.75, 2, 1755, 1755, 0, 1504, 1000, 1500, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'ItemRequester');
-- Profession Trainer
DELETE FROM `creature_template` WHERE (`entry`=993371);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES 
(993371, 0, 0, 0, 0, 0, 26789, 0, 0, 0, 'MMOwning Lehrmeister', 'Bildet euch aus', '', 0, 80, 80, 0, 35, 35, 1, 0.75, 2, 1755, 1755, 0, 1504, 1000, 1500, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'professionnpc');


-- Lotto
DELETE FROM game_event WHERE entry=132;
INSERT INTO game_event VALUES
(132, "2011-01-31 20:00:00", "2020-12-31 06:00:00", 1440, 1, 0, "Lotto!", 0);

DELETE FROM `creature_template` WHERE `entry`=999900;
INSERT INTO `creature_template` VALUES
('999900','0','0','0','0','0','108','0','0','0','Gl�cksfee','Lotto',NULL,'0','80','80','0','35','35','1','2.18','1.14286','1','3','509','683','0','805','45','1500','0','1','64','8','0','0','0','0','0','20','30','4','7','0','999901','0','0','0','0','0','0','0','0','48138','48142','59265','55266','53095','54098','27020','0','0','0','1305000','1595000','','0','3','310','2','1','0','0','0','0','0','0','0','0','1','0','617299803','0','npc_lotto','0');

DELETE FROM `npc_text` WHERE ID IN (999900, 999901);
INSERT INTO `npc_text` VALUES
('999900','','Willkommen, $N.$B$BM�chtest du an unserer Lotterie teilnehmen?$B$BKauf ein Los und du kannst um 20h der gl�ckliche Gewinner sein.$BLose kosten nur 50 Gold!','0','1','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','0'),
('999901','','$N, du hast heute schon ein Los gekauft!$B$BBitte warte die n�chste Ziehung ab!','0','1','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','','','0','0','0','0','0','0','0','0','0');

-- Custom Boss
DELETE FROM `creature_template` WHERE `entry` IN (980000, 980001, 980002, 980003, 980004, 980005, 980006);
INSERT INTO `creature_template` VALUES
('980000','0','0','0','0','0','17263','0','0','0','Likantropo','',NULL,'0','83','83','0','16','16','0','2.18','1.14286','2','3','509','683','0','805','45','1500','0','1','64','8','0','0','0','0','0','20','30','4','7','0','100011','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1305000','1595000','','0','3','310','2','1','0','0','0','0','0','0','0','0','1','0','617299803','0','npc_likantropo','0'),
('980001','0','0','0','0','0','23185','0','0','0','Lava Boost','',NULL,'0','83','83','0','16','16','0','2.18','1.14286','1.5','3','509','683','0','805','45','1500','0','8','64','8','0','0','0','0','0','20','30','4','7','0','100011','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1305000','1595000','','0','3','310','30','1','0','0','0','0','0','0','0','0','1','0','617299803','0','npc_lava_boost','0'),
('980002','0','0','0','0','0','4762','0','0','0','Quel''Nagas','',NULL,'0','83','83','0','16','16','0','2.18','1.14286','2','3','509','683','0','805','45','1500','0','8','64','8','0','0','0','0','0','20','30','4','7','0','100011','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1305000','1595000','','0','3','410','30','1','0','0','0','0','0','0','0','0','1','0','617299803','0','npc_quel_nagas','0'),
('980003','0','0','0','0','0','21741','0','0','0','Might of Sylvanas','',NULL,'0','83','83','0','16','16','0','2.18','1.14286','1.5','3','509','683','0','805','45','1500','0','8','64','8','0','0','0','0','0','20','30','4','7','0','100011','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1305000','1595000','','0','3','320','60','1','0','0','0','0','0','0','0','0','1','0','617299803','0','npc_might_of_sylvanas','0'),
('980004','0','0','0','0','0','25770','0','0','0','Trollzilla','',NULL,'0','83','83','0','16','16','0','2.18','1.14286','2','3','509','683','0','805','45','1500','0','1','64','8','0','0','0','0','0','20','30','4','7','0','100011','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1305000','1595000','','0','3','310','2','1','0','0','0','0','0','0','0','0','1','0','617299803','0','npc_trollzilla','0'),
('980005','0','0','0','0','0','11335','0','0','0','Perotharn','',NULL,'0','83','83','0','16','16','0','2.18','1.14286','1.5','3','509','683','0','805','45','1500','0','8','64','8','0','0','0','0','0','20','30','4','7','0','100011','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1305000','1595000','','0','3','310','30','1','0','0','0','0','0','0','0','0','1','0','617299803','0','npc_perotharn','0'),
('980006','0','0','0','0','0','8756','0','0','0','Uznam the Watcher','',NULL,'0','83','83','0','16','16','0','2.18','1.14286','2','3','509','683','0','805','45','1500','0','1','64','8','0','0','0','0','0','20','30','4','7','0','100011','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1305000','1595000','','0','3','310','2','1','0','0','0','0','0','0','0','0','1','0','617299803','0','npc_uznam_the_watcher','0');