#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("freeosconfig")]] freeosconfig : public eosio::contract {
  public:
    freeosconfig(name receiver, name code, datastream<const char*> ds):contract(receiver, code, ds) {}

    [[eosio::action]]
    void upsert(
            name virtualtable,
            name paramname,
            std::string value
          );

    [[eosio::action]]
    void erase ( name paramname );


  private:

    struct [[eosio::table]] parameter {
      name virtualtable;
      name paramname;
      std::string value;

      uint64_t primary_key() const { return paramname.value;}
      uint64_t get_secondary_1() const {return virtualtable.value;}
    };

  using parameter_index = eosio::multi_index<"parameters"_n, parameter,
  indexed_by<"virtualtable"_n, const_mem_fun<parameter, uint64_t, &parameter::get_secondary_1>>
  >;
};
