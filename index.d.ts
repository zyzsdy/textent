interface size{
    width: nubmer;
    height: number;
}
interface Textent{
    /**
     * Render string by fontname and fontsize.
     * @param fontName fontface name where you see at System dialog.
     * @param fontSize pixel number of font height.
     * @param destString the string you want to render.
     */
    render(fontName: string, fontSize: number, destString: string): size;
}

declare var textent: Textent
export default textent;