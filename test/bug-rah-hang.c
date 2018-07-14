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
	dogma_key_t slot;
	dogma_simple_capacitor_t* list;
	size_t llength;

	dogma_init();
	dogma_init_context(&ctx);

	assert(dogma_set_ship(ctx, 641) == DOGMA_OK);

	assert(dogma_add_module_s(ctx, 4403, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_s(ctx, 47777, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_s(ctx, 25898, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_sc(ctx, 3186, &slot, 21740, DOGMA_STATE_Active) == DOGMA_OK);

	assert(dogma_add_module_s(ctx, 11269, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_s(ctx, 10190, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_s(ctx, 448, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_s(ctx, 25896, &slot, DOGMA_STATE_Active) == DOGMA_OK);

	assert(dogma_add_module_s(ctx, 5051, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_s(ctx, 5839, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_s(ctx, 25896, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_sc(ctx, 3154, &slot, 21740, DOGMA_STATE_Active) == DOGMA_OK);

	assert(dogma_add_module_sc(ctx, 3154, &slot, 21740, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_sc(ctx, 3154, &slot, 21740, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_s(ctx, 5945, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_sc(ctx, 3154, &slot, 21740, DOGMA_STATE_Active) == DOGMA_OK);

	assert(dogma_add_module_s(ctx, 10190, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_s(ctx, 11269, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_s(ctx, 41057, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_sc(ctx, 3186, &slot, 21740, DOGMA_STATE_Active) == DOGMA_OK);

	assert(dogma_add_module_s(ctx, 47777, &slot, DOGMA_STATE_Active) == DOGMA_OK);
	assert(dogma_add_module_sc(ctx, 3154, &slot, 21740, DOGMA_STATE_Active) == DOGMA_OK);

	assert(dogma_get_capacitor_all(
			ctx,
			true,
			&list,
			&llength
		) == DOGMA_OK);

	dogma_free_context(ctx);
	return 0;
}
