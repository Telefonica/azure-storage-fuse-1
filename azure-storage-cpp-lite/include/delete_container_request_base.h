#pragma once

#include <map>
#include <string>

#include "storage_EXPORTS.h"

#include "http_base.h"
#include "storage_account.h"
#include "storage_request_base.h"

namespace microsoft_azure {
    namespace storage {

        class delete_container_request_base : public blob_request_base {
        public:
            virtual std::string container() const = 0;

            AZURE_STORAGE_API void build_request(const storage_account &a, http_base &h, const storage_client_key &k) const override;
        };

    }
}
