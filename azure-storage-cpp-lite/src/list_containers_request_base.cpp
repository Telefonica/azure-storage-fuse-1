#include "list_containers_request_base.h"

#include "constants.h"
#include "utility.h"

namespace microsoft_azure {
    namespace storage {

        void list_containers_request_base::build_request(const storage_account &a, http_base &h, const storage_client_key &/*k*/) const {
            const auto &r = *this;

            h.set_absolute_timeout(30L);
            
            h.set_method(http_base::http_method::get);

            storage_url url = a.get_url(storage_account::service::blob);
            url.append_path("");

            url.add_query(constants::query_comp, constants::query_comp_list);
            add_optional_query(url, constants::query_prefix, r.prefix());
            add_optional_query(url, constants::query_marker, r.marker());
            add_optional_query(url, constants::query_maxresults, r.maxresults());
            if (r.include_metadata()) {
                url.add_query(constants::query_include, constants::query_include_metadata);
            }
            add_optional_query(url, constants::query_timeout, r.timeout());
            h.set_url(url.to_string());

            storage_headers headers;
            add_ms_header(h, headers, constants::header_ms_client_request_id, r.ms_client_request_id(), true);

            h.add_header(constants::header_user_agent, constants::header_value_user_agent);
            add_ms_header(h, headers, constants::header_ms_date, get_ms_date(date_format::rfc_1123));
            add_ms_header(h, headers, constants::header_ms_version, constants::header_value_storage_version);

            a.credential()->sign_request(r, h, url, headers);
        }

    }
}
