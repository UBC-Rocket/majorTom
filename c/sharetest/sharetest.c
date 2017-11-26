/*
Main implementation of Shared Library Test board
*/

#include <stdint.h>

#include <sharetest/sharetest.h>
#include <general.h>
#include <shared/can.h>
#include <shared/init.h>
#include <shared/mock_utils.h>

int main()
{
	can_id_t id;
	uint64_t data;
	status_t rc;

	rc = initCanMock();
	if (rc != STATUS_OK) {
		#ifdef MOCK
		tsprintf("Mock CAN bus initialization error.\n");
		return rc;
		#endif
	}

	for (int i = 0; i < 1; i++) {
		rc = initCanTest();
		if (rc != STATUS_OK) {
			#ifdef MOCK
			tsprintf("Mock CAN bus test initialization error.\n");
			return rc;
			#endif
		}

		for (int i = 0; i < 10; i++) {
			rc = canRead(&id, &data);
			if (rc != STATUS_OK && rc != STATUS_CAN_FILTERED) {
				#ifdef MOCK
				tsprintf("Mock canRead() error.\n");
				return rc;
				#endif
			}
			rc = canWrite(id, data);
			if (rc != STATUS_OK) {
				#ifdef MOCK
				tsprintf("Mock canWrite() error.\n");
				return rc;
				#endif
			}
		}
	}

	tsprintf("Sharetest completed successfully!\n");
	return STATUS_OK;
}
