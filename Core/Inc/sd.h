#ifndef SD_H
#define SD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "fx_api.h"
#include <stdint.h>

UINT sd_init(void);
UINT sd_deinit(void);

UINT sd_csv_append_line(const CHAR *path, const CHAR *line);
UINT sd_csv_append_row(const CHAR *path, const CHAR * const *fields, UINT field_count);
UINT sd_csv_read_line(const CHAR *path, ULONG *offset, CHAR *buffer, UINT buffer_len, UINT *out_len);

FX_MEDIA *sd_get_media(void);
ULONG sd_get_total_sectors(void);

#ifdef __cplusplus
}
#endif

#endif /* SD_H */
