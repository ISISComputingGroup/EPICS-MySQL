/* MySQLTestMain.cpp */
/* Author:  Marty Kraimer Date:    17MAR2000 */

#include <stddef.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>
#include <cppconn/metadata.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/statement.h>
#include "mysql_driver.h"
#include "mysql_connection.h"


#include "epicsExit.h"
#include "epicsThread.h"
#include "iocsh.h"


int main(int argc,char *argv[])
{
    if(argc>=2) {    
        iocsh(argv[1]);
        epicsThreadSleep(.2);
    }


	try {
		sql::Driver * driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect("localhost", "report", "$report"));

		std::auto_ptr< sql::Statement > stmt(con->createStatement());

		stmt->execute("USE archive");

		{
			std::auto_ptr< sql::ResultSet > res(stmt->executeQuery("SELECT * from channel"));

			std::cout << "res->rowsCount() = " << res->rowsCount() << std::endl;
			while (res->next()) {
				std::cout << "name = '" << res->getString("name") << "'" << std::endl;
			}
		}

		stmt.reset(NULL); 

	} catch (sql::SQLException &e) {
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

	} catch (std::runtime_error &e) {

		std::cout << "# ERR: " << e.what() << std::endl;
	}


    iocsh(NULL);
    epicsExit(0);
    return(0);
}
