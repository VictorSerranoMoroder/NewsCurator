#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

class DatabaseConnection
{
	public:
		//Singleton Access Method
		static DatabaseConnection* getInstance();

		//Database Operation Functions
		mongocxx::database getDatabase(std::string databaseName);

		//Function Overloading for Singleton
		DatabaseConnection(DatabaseConnection& other) = delete;
		void operator=(const DatabaseConnection&) = delete;
		
	private:
		DatabaseConnection();
		static DatabaseConnection* databaseconnection_;
		mongocxx::client client;
};

