void main(void)
{
    output(1 < 2); /* 1 */
    output(1 < 1); /* 0 */
    output(1 < 0); /* 0 */

    output(1 <= 2); /* 1 */
    output(1 <= 1); /* 1 */
    output(1 <= 0); /* 0 */

    output(1 > 2); /* 0 */
    output(1 > 1); /* 0 */
    output(1 > 0); /* 1 */

    output(1 >= 2); /* 0 */
    output(1 >= 1); /* 1 */
    output(1 >= 0); /* 1 */

    output(1 == 2); /* 0 */
    output(1 == 1); /* 1 */
    output(1 == 0); /* 0 */

    output(1 != 2); /* 1 */
    output(1 != 1); /* 0 */
    output(1 != 0); /* 1 */

    output(1 + 2); /* 3 */
    output(1 + 1); /* 2 */
    output(1 + 0); /* 1 */

    output(1 - 2); /* -1 */
    output(1 - 1); /* 0  */
    output(1 - 0); /* 1  */

    output(1 * 2); /* 2 */
    output(1 * 1); /* 1 */
    output(1 * 0); /* 0 */

    output(1 / 2); /* 0     */
    output(1 / 1); /* 1     */
    output(1 / 0); /* error */
}
