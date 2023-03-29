#include "hash_table.c"

int main()
{
    hash_table hash;
    init_table(hash);

    insert_value_in_table(hash, "5", "a", "double");
    insert_value_in_table(hash, "8", "b", "double");
    insert_value_in_table(hash, "0", "c", "double");

    print_table(hash);

    insert_value_in_table(hash, "8", "a", "double");
    print_table(hash);
    insert_value_in_table(hash, "13", "a", "double");
    print_table(hash);

    node *x = get_item_by_name(hash, "a");
    node *y = get_item_by_name(hash, "b");
    // int z = x->value + y->value;

    // update(hash, z, "c");
    print_table(hash);

    return 0;
}