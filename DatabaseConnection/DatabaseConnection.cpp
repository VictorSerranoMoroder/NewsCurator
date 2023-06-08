#pragma once
#include "DatabaseConnection.h"

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

DatabaseConnection* DatabaseConnection::databaseconnection_ = nullptr;
static mongocxx::instance instance{};

DatabaseConnection::DatabaseConnection()
{	
	try 
	{	
		mongocxx::uri uri("mongodb://localhost:27017");
		client = mongocxx::client{ uri };
	}
	catch (const std::exception& xcp) 
	{
		std::cout << "connection failed: " << xcp.what() << std::endl;
	}
	
}

DatabaseConnection* DatabaseConnection::getInstance()
{
	if (databaseconnection_ == nullptr) {
		databaseconnection_ = new DatabaseConnection();
	}
	return databaseconnection_;
}

mongocxx::database DatabaseConnection::getDatabase(std::string databaseName)
{
	mongocxx::database db;
	try
	{
		db = client[databaseName];
		return db;
	}
	catch (const std::exception& xcp)
	{
		std::cout << xcp.what() << std::endl;
	}

	return db;
}