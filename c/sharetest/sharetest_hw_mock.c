/*
Mock implementation of Shared Library Test board hardware-dependent functions
*/

#include <stdint.h>

#include <general.h>
#include <sharetest.h>

#include <shared/utils.h>
#include <shared/init.h>
#include <shared/can.h>
#include <shared/sd.h>

/**
 * @brief Shared Library Test board routine - mock implementation (Tests the shared library)
 * @return Status.
 */
int main()
{
	tsprintf("Sharetest starting\n");
	status_t rc;
	rc = platformInit();
	if (rc != STATUS_OK) {
		tsprintf("paltformInit returned <%d>\n", rc);
		return rc;
	}

	/* SD tests */
	rc = sdInit();
	if (rc != STATUS_OK) {
		tsprintf("sdInit returned <%d>\n", rc);
		return rc;
	}

	tsprintf("Start SD logging tests...\n");

	rc = sdWriteString("foo bar par");
	if (rc != STATUS_OK) {
		tsprintf("sdWriteString returned <%d>\n", rc);
		return rc;
	}

	double output[] = {0, 2, 5.04, 7.66};
	rc = sdWriteDouble(output, 4);
	if (rc != STATUS_OK) {
		tsprintf("sdWriteString returned <%d>\n", rc);
		return rc;
	}

	tsprintf("Finished SD logging tests.\n");

	can_id_t id;
	uint64_t data;

	/* CAN tests */
	rc = canInit();
	if (rc != STATUS_OK) {
		tsprintf("canInit returned <%d>\n", rc);
		return rc;
	}

	for (int i = 0; i < 10; i++) {
		rc = canRead(&id, &data);
		if (rc != STATUS_OK && rc != STATUS_CAN_FILTERED) {
			tsprintf("canRead returned <%d>\n", rc);
			return rc;
		}

		rc = canWrite(id, data);
		if (rc != STATUS_OK) {
			tsprintf("canWrite returned <%d>\n", rc);
			return rc;
		}
	}

	tsprintf("Sharetest exiting\n");
	return 0;
}