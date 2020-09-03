#include <eosio/eosio.hpp>
#include "freeosconfig.hpp"

using namespace eosio;

[[eosio::action]]
void freeosconfig::upsert(
        name virtualtable,
        name paramname,
        std::string value
        ) {

    parameter_index parameters(get_self(), get_first_receiver().value);
    auto iterator = parameters.find(paramname.value);

    // check if the parameter is in the table or not
    if (iterator == parameters.end() ) {
        // the parameter is not in the table, so insert
        parameters.emplace(_self, [&](auto & row) {  // first argument was "freeosconfig"_n
           row.virtualtable = virtualtable;
           row.paramname = paramname;
           row.value = value;
        });

    } else {
        // the parameter is in the table, so update
        parameters.modify(iterator, _self, [&](auto& row) {   // second argument was "freeosconfig"_n
          row.virtualtable = virtualtable;
          row.paramname = paramname;
          row.value = value;
        });
    }
}

// erase parameter from the table
[[eosio::action]]
void freeosconfig::erase ( name paramname ) {
    require_auth(_self);

    parameter_index parameters(get_self(), get_first_receiver().value);
    auto iterator = parameters.find(paramname.value);

    // check if the parameter is in the table or not
    check(iterator != parameters.end(), "Record does not exist");

    // the parameter is in the table, so delete
    parameters.erase(iterator);
}
