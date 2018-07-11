/* libdogma
 * Copyright (C) 2013 Romain "Artefact2" Dalmaso <artefact2@gmail.com>
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
	dogma_context_t* ctx;
	dogma_key_t slot0, slot1, slot2;
	double v;

	dogma_init();
	dogma_init_context(&ctx);

	/* Source: Pyfa-1.10.0 */

	/* 645:4405;1:24438;1:25920;1:28211;1:: */
	dogma_set_ship(ctx, TYPE_Dominix);
	assert(dogma_get_drone_attribute(ctx, TYPE_GardeII, ATT_ArmorHP, &v) == DOGMA_NOT_FOUND);

	dogma_add_drone(ctx, TYPE_GardeII, 2);
	assertok(dogma_get_drone_attribute(ctx, TYPE_GardeII, ATT_ArmorHP, &v));
	assertf(1800.0, v, 0.05);

	dogma_remove_drone_partial(ctx, TYPE_GardeII, 1);
	assertok(dogma_get_drone_attribute(ctx, TYPE_GardeII, ATT_ArmorHP, &v));
	assertf(1800.0, v, 0.05);

	dogma_remove_drone_partial(ctx, TYPE_GardeII, 1);
	assert(dogma_get_drone_attribute(ctx, TYPE_GardeII, ATT_ArmorHP, &v) == DOGMA_NOT_FOUND);

	dogma_add_drone(ctx, TYPE_GardeII, 5);
	dogma_remove_drone_partial(ctx, TYPE_GardeII, 10);
	assert(dogma_get_drone_attribute(ctx, TYPE_GardeII, ATT_ArmorHP, &v) == DOGMA_NOT_FOUND);

	dogma_add_drone(ctx, TYPE_GardeII, 10);
	dogma_remove_drone(ctx, TYPE_GardeII);
	assert(dogma_get_drone_attribute(ctx, TYPE_GardeII, ATT_ArmorHP, &v) == DOGMA_NOT_FOUND);

	dogma_add_drone(ctx, TYPE_GardeII, 1);
	dogma_get_drone_attribute(ctx, TYPE_GardeII, ATT_MaxRange, &v);
	assertf(30938, v, 1);
	dogma_get_drone_attribute(ctx, TYPE_GardeII, ATT_TrackingSpeed, &v);
	assertf(0.0462, v, 0.00005);

	dogma_add_module(ctx, TYPE_LargeSentryDamageAugmentorI, &slot0);
	dogma_add_module(ctx, TYPE_DroneDamageAmplifierII, &slot1);
	dogma_add_module(ctx, TYPE_OmnidirectionalTrackingLinkII, &slot2);
	dogma_set_module_state(ctx, slot0, DOGMA_STATE_Online);
	dogma_set_module_state(ctx, slot1, DOGMA_STATE_Online);
	dogma_set_module_state(ctx, slot2, DOGMA_STATE_Online);
	dogma_get_drone_attribute(ctx, TYPE_GardeII, ATT_MaxRange, &v);
	assertf(30937.5, v, 0.05);
	dogma_get_drone_attribute(ctx, TYPE_GardeII, ATT_TrackingSpeed, &v);
	assertf(0.0462, v, 0.0000005);
	dogma_get_drone_attribute(ctx, TYPE_GardeII, ATT_DamageMultiplier, &v);
	assertf(6.685757038689796, v, 0.000000000005);

	dogma_free_context(ctx);

	dogma_init_context(&ctx);
	dogma_set_ship(ctx, TYPE_Scorpion);
	dogma_add_drone(ctx, TYPE_HornetEC300, 1);
	dogma_add_module(ctx, TYPE_SignalDistortionAmplifierII, &slot0);
	dogma_add_module(ctx, TYPE_LadarECMII, &slot1);
	dogma_set_module_state(ctx, slot0, DOGMA_STATE_Online);
	dogma_set_module_state(ctx, slot1, DOGMA_STATE_Active);

	/* Ship-related ECM bonuses should not apply to the drone */
	dogma_get_drone_attribute(ctx, TYPE_HornetEC300, ATT_ScanLadarStrengthBonus, &v);
	assertf(1.0, v, 0.05);

	/* …But they should apply to the ECM module */
	dogma_get_module_attribute(ctx, slot1, ATT_ScanLadarStrengthBonus, &v);
	assertf(8.6625, v, 0.00005);

	dogma_free_context(ctx);
	return 0;
}
