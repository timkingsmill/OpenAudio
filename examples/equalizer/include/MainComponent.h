#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <JuceHeader.h>
#include "DebugComponent.h"
#include "AudioInputDebugView.h"

//==============================================================================

/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

/*
Pseudocode / Plan (detailed):
1. Add Doxygen-style documentation comments to the `MainComponent` class and all
   publicly visible methods and important private members in the selected range.
2. For each method override (paint, resized, lookAndFeelChanged, etc.) provide:
   - Brief description of purpose.
   - Notes about behavior/ownership where relevant.
3. For the `CommandIDs` enum, document what each command does and any numeric
   considerations.
4. For ApplicationCommandTarget and MenuBarModel overrides, document their role
   in command dispatch and menu construction.
5. For private members exposed in the selected range, document their role and
   ownership semantics (e.g., `std::unique_ptr` usage).
6. Ensure comments are concise, consistent, and suitable for Doxygen generation.
*/

/**
 * @brief Top-level main component for the equalizer example application.
 *
 * This component hosts the UI controls and handles application-level services such
 * as menu construction, command routing and device management. It implements
 * `juce::ApplicationCommandTarget` to integrate with the JUCE command system,
 * `juce::MenuBarModel` to provide the application menu, and `juce::Component` to
 * provide the visible UI.
 */
class MainComponent final :
    public juce::ApplicationCommandTarget,
    public juce::Component,
    public juce::MenuBarModel
{
public:
    //==============================================================================
    /**
     * @brief Constructs the main component.
     *
     * Responsible for initializing member objects (audio device manager, command
     * manager, debug UI, and menu bar) and registering application commands.
     */
    MainComponent();

    /**
     * @brief Virtual destructor.
     *
     * Ensures proper teardown of JUCE objects and owned pointers. Marked `override`
     * to reflect override of `juce::Component` destructor semantics.
     */
    ~MainComponent() override;

    //==============================================================================
    /**
     * @brief Paints this component.
     *
     * Called by JUCE when the component needs to be repainted. Implementations
     * should draw the component background and any custom graphics here.
     *
     * @param g Graphics context used for drawing.
     */
    void paint (juce::Graphics&) override;

    /**
     * @brief Called when this component is resized.
     *
     * Use this to lay out child components and respond to size changes.
     */
    void resized() override;

    /**
     * @brief Identifiers for application commands exposed by this component.
     *
     * These IDs are used with the `juce::ApplicationCommandManager` to register
     * and invoke commands from menus, keyboard shortcuts, and other UI sources.
     */
    enum CommandIDs
    {
        /** Show the audio device settings / setup dialog. */
        audioSetupCommandID = 1,

        /** Exit the application. */
        exitAppCommandID
    };

    //==============================================================================
private:
    /**
     * @brief Show a dialog window used by the application (e.g., audio settings).
     *
     * Creates and displays a `juce::DialogWindow` instance, storing a `SafePointer`
     * so the dialog can be tracked and safely accessed without creating ownership
     * cycles.
     */
    void showDialogWindow();


    // Inherited via ApplicationCommandTarget
    /**
     * @brief Returns the next command target in the command routing chain.
     *
     * Used by JUCE to propagate commands to parent components or application-level
     * handlers if this component does not handle them.
     *
     * @return Pointer to the next `ApplicationCommandTarget`, or nullptr.
     */
    ApplicationCommandTarget* getNextCommandTarget() override;

    /**
     * @brief Populates `commands` with the set of command IDs this target supports.
     *
     * JUCE calls this to determine which commands to query for `getCommandInfo`.
     *
     * @param commands Array to be filled with supported `juce::CommandID` values.
     */
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;

    /**
     * @brief Provides metadata (name, description, default keypress) for a command.
     *
     * Used by application menus and key mappings to show human-readable information
     * about a command.
     *
     * @param commandID The command identifier to describe.
     * @param result Output parameter to be populated with command information.
     */
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;

    /**
     * @brief Execute a command identified by `info`.
     *
     * Performs the action associated with the requested command and returns whether
     * it was successfully handled.
     *
     * @param info Invocation information containing the command id and any parameters.
     * @return true if the command was handled, false otherwise.
     */
    bool perform(const InvocationInfo& info) override;

    // Inherited via MenuBarModel
    /**
     * @brief Returns the array of top-level menu names for the menu bar.
     *
     * The returned list will be used by `juce::MenuBarComponent` to construct menus.
     *
     * @return A `juce::StringArray` of menu names (e.g., "File", "Edit", ...).
     */
    juce::StringArray getMenuBarNames() override;

    /**
     * @brief Returns the menu contents for the menu at `menuIndex`.
     *
     * Build and return a `juce::PopupMenu` for the requested index. The `menuName`
     * can be used to disambiguate or localize content.
     *
     * @param menuIndex Index of the menu requested.
     * @param menuName Localized menu name for reference.
     * @return A `juce::PopupMenu` instance describing the menu items.
     */
    juce::PopupMenu getMenuForIndex(int menuIndex, const juce::String& menuName) override;

    /**
     * @brief Called when a menu item is selected.
     *
     * Receives the selected `menuItemID` and the index of the menu that produced it.
     *
     * @param menuItemID Identifier for the selected menu item (typically CommandID).
     * @param menuIndex Index of the menu that contained the item.
     */
    void menuItemSelected(int menuItemID, int menuIndex) override;

    // Inherited via Component
    /**
     * @brief Called when the look-and-feel for the component changes.
     *
     * Override this to update any cached fonts, colours or to re-parent child
     * components that depend on the current look-and-feel.
     */
    void lookAndFeelChanged() override;


private:
    //==============================================================================
    /**
     * @brief Stores application-wide properties (persisted settings).
     *
     * `juce::ApplicationProperties` provides access to a properties file and
     * allows the app to save/recall user preferences across runs.
     */
    juce::ApplicationProperties _applicationProperties;

    /**
     * @brief Manages audio device configuration and callbacks.
     *
     * Responsible for opening/closing audio devices and providing audio I/O to
     * the rest of the application.
     * `std::unique_ptr` expresses exclusive ownership.
     * The `AudioDeviceManager` is created and destroyed along with the `MainComponent`.
     */
    std::unique_ptr<juce::AudioDeviceManager> _audioDeviceManager;

    /**
     * @brief Optional debug UI component owned by this main component.
     *
     * `std::unique_ptr` expresses exclusive ownership; the `DebugComponent` is
     * created and destroyed along with the `MainComponent`.
     */
    //std::unique_ptr<DebugComponent> _debugComponent;

    /**
     * @brief Optional audio input debug view component owned by this main component.
     *
     * `std::unique_ptr` expresses exclusive ownership; the `AudioInputDebugView` is
     * created and destroyed along with the `MainComponent`.
     */
    std::unique_ptr<AudioInputDebugView> _audioInputDebugView;


    /**
     * @brief The menu bar component shown at the top of the application window.
     *
     * Owned by this component and constructed from the `MenuBarModel` implemented
     * by this class.
     */
    std::unique_ptr<juce::MenuBarComponent> _menuBarComponent;

    /**
     * @brief Manages application commands and keyboard mappings.
     *
     * Registers commands exposed by `MainComponent` and routes invocations coming
     * from the menu bar, keypresses or other UI elements.
     */
    juce::ApplicationCommandManager _commandManager;

    /**
     * @brief Safe pointer to an optional dialog window created by this component.
     *
     * `SafePointer` allows the code to refer to the dialog without creating a
     * strong ownership link; it becomes `nullptr` automatically if the dialog is destroyed.
     */
    juce::Component::SafePointer<juce::DialogWindow> _dialogWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
