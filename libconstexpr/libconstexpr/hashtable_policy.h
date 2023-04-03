#ifndef LIBCONSTEXPR_HASHTABLE_H
#define LIBCONSTEXPR_HASHTABLE_H

#include <array>
#include <concepts>
#include <cstddef>

namespace libconstexpr {
    namespace hashtable {
        template <typename T>
        concept size_policy_concept = requires(T t, std::size_t n) {
            { t.next(n) } -> std::same_as<std::size_t>;
        };

        // Primes taken from gcc
        constexpr std::array<std::size_t, 256 + 48 + 1> primes{
            2uz, 3uz, 5uz, 7uz, 11uz, 13uz, 17uz, 19uz, 23uz, 29uz, 31uz, 37uz,
            41uz, 43uz, 47uz, 53uz, 59uz, 61uz, 67uz, 71uz, 73uz, 79uz, 83uz,
            89uz, 97uz, 103uz, 109uz, 113uz, 127uz, 137uz, 139uz, 149uz, 157uz,
            167uz, 179uz, 193uz, 199uz, 211uz, 227uz, 241uz, 257uz, 277uz,
            293uz, 313uz, 337uz, 359uz, 383uz, 409uz, 439uz, 467uz, 503uz,
            541uz, 577uz, 619uz, 661uz, 709uz, 761uz, 823uz, 887uz, 953uz,
            1031uz, 1109uz, 1193uz, 1289uz, 1381uz, 1493uz, 1613uz, 1741uz,
            1879uz, 2029uz, 2179uz, 2357uz, 2549uz, 2753uz, 2971uz, 3209uz,
            3469uz, 3739uz, 4027uz, 4349uz, 4703uz, 5087uz, 5503uz, 5953uz,
            6427uz, 6949uz, 7517uz, 8123uz, 8783uz, 9497uz, 10273uz, 11113uz,
            12011uz, 12983uz, 14033uz, 15173uz, 16411uz, 17749uz, 19183uz,
            20753uz, 22447uz, 24281uz, 26267uz, 28411uz, 30727uz, 33223uz,
            35933uz, 38873uz, 42043uz, 45481uz, 49201uz, 53201uz, 57557uz,
            62233uz, 67307uz, 72817uz, 78779uz, 85229uz, 92203uz, 99733uz,
            107897uz, 116731uz, 126271uz, 136607uz, 147793uz, 159871uz,
            172933uz, 187091uz, 202409uz, 218971uz, 236897uz, 256279uz,
            277261uz, 299951uz, 324503uz, 351061uz, 379787uz, 410857uz,
            444487uz, 480881uz, 520241uz, 562841uz, 608903uz, 658753uz,
            712697uz, 771049uz, 834181uz, 902483uz, 976369uz, 1056323uz,
            1142821uz, 1236397uz, 1337629uz, 1447153uz, 1565659uz, 1693859uz,
            1832561uz, 1982627uz, 2144977uz, 2320627uz, 2510653uz, 2716249uz,
            2938679uz, 3179303uz, 3439651uz, 3721303uz, 4026031uz, 4355707uz,
            4712381uz, 5098259uz, 5515729uz, 5967347uz, 6456007uz, 6984629uz,
            7556579uz, 8175383uz, 8844859uz, 9569143uz, 10352717uz, 11200489uz,
            12117689uz, 13109983uz, 14183539uz, 15345007uz, 16601593uz,
            17961079uz, 19431899uz, 21023161uz, 22744717uz, 24607243uz,
            26622317uz, 28802401uz, 31160981uz, 33712729uz, 36473443uz,
            39460231uz, 42691603uz, 46187573uz, 49969847uz, 54061849uz,
            58488943uz, 63278561uz, 68460391uz, 74066549uz, 80131819uz,
            86693767uz, 93793069uz, 101473717uz, 109783337uz, 118773397uz,
            128499677uz, 139022417uz, 150406843uz, 162723577uz, 176048909uz,
            190465427uz, 206062531uz, 222936881uz, 241193053uz, 260944219uz,
            282312799uz, 305431229uz, 330442829uz, 357502601uz, 386778277uz,
            418451333uz, 452718089uz, 489790921uz, 529899637uz, 573292817uz,
            620239453uz, 671030513uz, 725980837uz, 785430967uz, 849749479uz,
            919334987uz, 994618837uz, 1076067617uz, 1164186217uz, 1259520799uz,
            1362662261uz, 1474249943uz, 1594975441uz, 1725587117uz,
            1866894511uz, 2019773507uz, 2185171673uz, 2364114217uz,
            2557710269uz, 2767159799uz, 2993761039uz, 3238918481uz,
            3504151727uz, 3791104843uz, 4101556399uz, 4294967291uz,
            // Sentinel, so we don't have to test the result of
            // lower_bound, or, on 64-bit machines, rest of the table.
            sizeof(std::size_t) != 8 ? 4294967291uz : 6442450933uz,
            8589934583uz, 12884901857uz, 17179869143uz, 25769803693uz,
            34359738337uz, 51539607367uz, 68719476731uz, 103079215087uz,
            137438953447uz, 206158430123uz, 274877906899uz, 412316860387uz,
            549755813881uz, 824633720731uz, 1099511627689uz, 1649267441579uz,
            2199023255531uz, 3298534883309uz, 4398046511093uz, 6597069766607uz,
            8796093022151uz, 13194139533241uz, 17592186044399uz,
            26388279066581uz, 35184372088777uz, 52776558133177uz,
            70368744177643uz, 105553116266399uz, 140737488355213uz,
            211106232532861uz, 281474976710597uz, 562949953421231uz,
            1125899906842597uz, 2251799813685119uz, 4503599627370449uz,
            9007199254740881uz, 18014398509481951uz, 36028797018963913uz,
            72057594037927931uz, 144115188075855859uz, 288230376151711717uz,
            576460752303423433uz, 1152921504606846883uz, 2305843009213693951uz,
            4611686018427387847uz, 9223372036854775783uz,
            18446744073709551557uz, 18446744073709551557uz};

        struct prime_size_policy {
            static constexpr std::size_t next(std::size_t n) {
                static_assert(primes.size() > 2);

                std::size_t last = primes[0];
                for (std::size_t i = 1; i < primes.size(); ++i) {
                    std::size_t current = primes[i];

                    if (current >= n) {
                        return current;
                    }

                    if (last == current) {
                        return current;
                    }

                    last = current;
                }

                return last;
            }
        };

        template <typename T, typename Value>
        concept node_concept = requires(const T t) {
            { t.hash() } -> std::same_as<std::size_t>;
            // FIXME: add check to make sure that hash is constexpr

            { t.value } -> std::same_as<const Value&>;
        };

        template <typename Hash, typename Value>
        struct hashless_node {
            const Value value;

            [[nodiscard]] constexpr std::size_t hash() const {
                return Hash{}(value);
            }
        };

        template <typename Hash, typename Value>
        struct hashfull_node {
            const Value value;
            const std::size_t cached_hash{Hash{}(value)};

            [[nodiscard]] constexpr std::size_t hash() const {
                return cached_hash;
            }
        };
    } // namespace hashtable

} // namespace libconstexpr

#endif // LIBCONSTEXPR_HASHTABLE_H
