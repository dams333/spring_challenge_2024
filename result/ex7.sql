WITH params AS(
    SELECT
        puKeys.N as pubN,
        prKeys.D as privD
    FROM primeFactors as prFact
    JOIN publicKeys as puKeys
        ON prFact.P * prFact.Q = puKeys.N
    JOIN privateKeys as prKeys
        ON (puKeys.E::bigint * prKeys.D::bigint) % ((prFact.P::bigint - 1) * (prFact.Q::bigint - 1)) = 1
)
SELECT
    encr.messageIndex as messageIndex,
    CHAR(
        POWER(
            POWER(
                POWER(
                    POWER(
                        POWER(
                            POWER(
                                POWER(
                                    POWER(
                                        POWER(
                                            POWER(
                                                POWER(
                                                    POWER(
                                                        POWER(
                                                            POWER(
                                                                POWER(
                                                                    POWER(
                                                                        POWER(
                                                                            POWER(
                                                                                POWER(
                                                                                    POWER(
                                                                                        POWER(
                                                                                            POWER(
                                                                                                POWER(
                                                                                                    CASE WHEN RSHIFT(p.privD, 23) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                                    2
                                                                                                ) % p.pubN
                                                                                                * CASE WHEN RSHIFT(p.privD, 22) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                                2
                                                                                            ) % p.pubN
                                                                                            * CASE WHEN RSHIFT(p.privD, 21) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                            2
                                                                                        ) % p.pubN
                                                                                        * CASE WHEN RSHIFT(p.privD, 20) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                        2
                                                                                    ) % p.pubN
                                                                                    * CASE WHEN RSHIFT(p.privD, 19) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                    2
                                                                                ) % p.pubN
                                                                                * CASE WHEN RSHIFT(p.privD, 18) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                2
                                                                            ) % p.pubN
                                                                            * CASE WHEN RSHIFT(p.privD, 17) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                            2
                                                                        ) % p.pubN
                                                                        * CASE WHEN RSHIFT(p.privD, 16) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                        2
                                                                    ) % p.pubN
                                                                    * CASE WHEN RSHIFT(p.privD, 15) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                    2
                                                                ) % p.pubN
                                                                * CASE WHEN RSHIFT(p.privD, 14) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                2
                                                            ) % p.pubN
                                                            * CASE WHEN RSHIFT(p.privD, 13) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                            2
                                                        ) % p.pubN
                                                        * CASE WHEN RSHIFT(p.privD, 12) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                        2
                                                    ) % p.pubN
                                                    * CASE WHEN RSHIFT(p.privD, 11) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                    2
                                                ) % p.pubN
                                                * CASE WHEN RSHIFT(p.privD, 10) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                2
                                            ) % p.pubN
                                            * CASE WHEN RSHIFT(p.privD, 9) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                            2
                                        ) % p.pubN
                                        * CASE WHEN RSHIFT(p.privD, 8) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                        2
                                    ) % p.pubN
                                    * CASE WHEN RSHIFT(p.privD, 7) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                    2
                                ) % p.pubN
                                * CASE WHEN RSHIFT(p.privD, 6) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                2
                            ) % p.pubN
                            * CASE WHEN RSHIFT(p.privD, 5) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                            2
                        ) % p.pubN
                        * CASE WHEN RSHIFT(p.privD, 4) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                        2
                    ) % p.pubN
                    * CASE WHEN RSHIFT(p.privD, 3) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                    2
                ) % p.pubN
                * CASE WHEN RSHIFT(p.privD, 2) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                2
            ) % p.pubN
            * CASE WHEN RSHIFT(p.privD, 1) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
            2
        ) % p.pubN
        * CASE WHEN RSHIFT(p.privD, 0) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN
    ) as decrypted
FROM EncryptedMessages as encr
JOIN params as p ON
    -- (encr.EncryptedMessage ^ p.privD) % p.pubN < 256
    -- bit by bit to avoid big numbers
    (
        POWER(
            POWER(
                POWER(
                    POWER(
                        POWER(
                            POWER(
                                POWER(
                                    POWER(
                                        POWER(
                                            POWER(
                                                POWER(
                                                    POWER(
                                                        POWER(
                                                            POWER(
                                                                POWER(
                                                                    POWER(
                                                                        POWER(
                                                                            POWER(
                                                                                POWER(
                                                                                    POWER(
                                                                                        POWER(
                                                                                            POWER(
                                                                                                POWER(
                                                                                                    CASE WHEN RSHIFT(p.privD, 23) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                                    2
                                                                                                ) % p.pubN
                                                                                                * CASE WHEN RSHIFT(p.privD, 22) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                                2
                                                                                            ) % p.pubN
                                                                                            * CASE WHEN RSHIFT(p.privD, 21) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                            2
                                                                                        ) % p.pubN
                                                                                        * CASE WHEN RSHIFT(p.privD, 20) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                        2
                                                                                    ) % p.pubN
                                                                                    * CASE WHEN RSHIFT(p.privD, 19) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                    2
                                                                                ) % p.pubN
                                                                                * CASE WHEN RSHIFT(p.privD, 18) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                                2
                                                                            ) % p.pubN
                                                                            * CASE WHEN RSHIFT(p.privD, 17) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                            2
                                                                        ) % p.pubN
                                                                        * CASE WHEN RSHIFT(p.privD, 16) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                        2
                                                                    ) % p.pubN
                                                                    * CASE WHEN RSHIFT(p.privD, 15) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                    2
                                                                ) % p.pubN
                                                                * CASE WHEN RSHIFT(p.privD, 14) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                                2
                                                            ) % p.pubN
                                                            * CASE WHEN RSHIFT(p.privD, 13) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                            2
                                                        ) % p.pubN
                                                        * CASE WHEN RSHIFT(p.privD, 12) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                        2
                                                    ) % p.pubN
                                                    * CASE WHEN RSHIFT(p.privD, 11) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                    2
                                                ) % p.pubN
                                                * CASE WHEN RSHIFT(p.privD, 10) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                                2
                                            ) % p.pubN
                                            * CASE WHEN RSHIFT(p.privD, 9) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                            2
                                        ) % p.pubN
                                        * CASE WHEN RSHIFT(p.privD, 8) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                        2
                                    ) % p.pubN
                                    * CASE WHEN RSHIFT(p.privD, 7) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                    2
                                ) % p.pubN
                                * CASE WHEN RSHIFT(p.privD, 6) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                                2
                            ) % p.pubN
                            * CASE WHEN RSHIFT(p.privD, 5) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                            2
                        ) % p.pubN
                        * CASE WHEN RSHIFT(p.privD, 4) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                        2
                    ) % p.pubN
                    * CASE WHEN RSHIFT(p.privD, 3) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                    2
                ) % p.pubN
                * CASE WHEN RSHIFT(p.privD, 2) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
                2
            ) % p.pubN
            * CASE WHEN RSHIFT(p.privD, 1) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN::bigint,
            2
        ) % p.pubN
        * CASE WHEN RSHIFT(p.privD, 0) % 2 = 1 THEN encr.EncryptedMessage ELSE 1 END % p.pubN
    )::bigint < 256
ORDER BY encr.messageIndex ASC
