#pragma once
/**
 *  @file raii_connection.h
 *  @date 21.03.2014
 *  @author mkoenig
 *  @brief 
 *
 *  $LastChangedDate: 2014-12-05 08:55:14 +0100 (Fr, 05 Dez 2014) $
 *  $LastChangedBy: mkoenig $
 *  $LastChangedRevision: 21240 $
 *
 */


#include "cpp_odbc/level2/handles.h"
#include "cpp_odbc/connection.h"

#include "psapp/pattern/pimpl.h"
#include "psapp/valid_ptr_core.h"

#include <string>

namespace cpp_odbc { namespace level2 {
	class api;
} }

namespace cpp_odbc {

class raii_environment;

/**
 * @brief This class is an implementation of the connection interface. It manages the life time
 *        of a level2::connection_handle and forwards calls to the level2 API associated with
 *        the given environment.
 */
class raii_connection : public connection {
public:
	/**
	 * @brief Create a new raii_connection
	 * @param environment The connection lives in this environment. The environment is kept alive for
	 *                    the life time of this object. The environment also contains the level2 API
	 *                    to which all calls are forwarded.
	 * @param connection_string The connection is created using this connection string.
	 */
	raii_connection(psapp::valid_ptr<raii_environment const> environment, std::string const & connection_string);

	/**
	 * @brief Retrieve the API instance associated with this environment.
	 * @return The associated API instance
	 */
	psapp::valid_ptr<level2::api const> get_api() const;

	/**
	 * @brief Retrieve the non-raii connection_handle which you can use in level 2 API calls.
	 * @return The non-raii connection_handle
	 */
	level2::connection_handle const & get_handle() const;

private:
	std::shared_ptr<statement> do_make_statement() const final;
	void do_set_attribute(SQLINTEGER attribute, long value) const final;
	void do_commit() const final;
	void do_rollback() const final;
	std::string do_get_string_info(SQLUSMALLINT info_type) const final;

	struct intern;
	psapp::pattern::pimpl<raii_connection> impl_;
};

}
