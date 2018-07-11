/* libdogma
 * Copyright (C) 2013, 2015 Romain "Artefact2" Dalmaso <artefact2@gmail.com>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "test.h"

int main(void) {
	dogma_context_t *ctxA, *ctxB;
	dogma_fleet_context_t* fctx;
	dogma_key_t slots[20];
	double v;
	bool found;

	dogma_init();
	dogma_init_context(&ctxA); /* 22544:17482;1:: */
	dogma_init_context(&ctxB); /* 28606:4274;1:4276;1:4278;1:: */
	dogma_init_fleet_context(&fctx);

	dogma_add_squad_commander(fctx, 0, 0, ctxB);
	dogma_add_squad_member(fctx, 0, 0, ctxA);

	dogma_set_ship(ctxA, TYPE_Hulk);
	dogma_set_ship(ctxB, TYPE_Orca);

	dogma_add_module_s(ctxB, TYPE_MiningForemanLinkHarvesterCapacitorEfficiencyII, &slots[10], DOGMA_STATE_Active);
	dogma_add_module_s(ctxB, TYPE_MiningForemanLinkLaserOptimizationII, &slots[11], DOGMA_STATE_Active);
	dogma_add_module_s(ctxB, TYPE_MiningForemanLinkMiningLaserFieldEnhancementII, &slots[12], DOGMA_STATE_Active);

	dogma_add_module_s(ctxA, TYPE_StripMinerI, &slots[0], DOGMA_STATE_Active);

	/* Source: Pyfa 1.10.0 */

	dogma_get_module_attribute(ctxA, slots[0], ATT_Duration, &v);
	assertf(103275, v, 0.05);

	dogma_set_module_state(ctxB, slots[11], DOGMA_STATE_Online);
	dogma_get_module_attribute(ctxA, slots[0], ATT_Duration, &v);
	assertf(103275.0, v, 0.05);

	dogma_set_default_skill_level(ctxB, 0);
	dogma_get_module_attribute(ctxA, slots[0], ATT_MiningAmount, &v);
	assertf(1054.6875, v, 0.005);
	dogma_set_default_skill_level(ctxB, 5);
	dogma_get_module_attribute(ctxA, slots[0], ATT_MiningAmount, &v);
	assertf(1054.6875, v, 0.0005);
	dogma_set_default_skill_level(ctxA, 0);
	dogma_get_module_attribute(ctxA, slots[0], ATT_MiningAmount, &v);
	assertf(675.0, v, 0.05);

	dogma_set_default_skill_level(ctxA, 5);
	/* The implant should replace the bonus from the Mining Foreman link */
	dogma_add_implant(ctxB, TYPE_MiningForemanMindlink, &slots[13]);
	dogma_set_module_state(ctxB, slots[11], DOGMA_STATE_Active);
	dogma_get_module_attribute(ctxA, slots[0], ATT_MiningAmount, &v);
	assertf(1054.6875, v, 0.00005);

	assertok(dogma_remove_fleet_member(fctx, ctxA, &found));
	assert(found == true);
	assertok(dogma_remove_fleet_member(fctx, ctxA, &found));
	assert(found == false);
	assertok(dogma_remove_fleet_member(fctx, ctxB, &found));
	assert(found == true);

	dogma_free_context(ctxA);
	dogma_free_context(ctxB);
	dogma_free_fleet_context(fctx);
	return 0;
}
